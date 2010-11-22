/* ********************************************* *
 * Writing Portable Device Drivers               *
 *                                               *
 * Implements PORT functions.                    *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#include "labport.h"
#include "labreg.h"
#include "labapi.h"

void write_reg(UINT8 addr, UINT8 data) {
	*((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER))) = data;
}

void write_reg_bit(UINT8 addr, UINT8 bitNum)
{
	/* individual register bit masking */
	write_reg(addr, 0);
	*((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER))) |= (1<<bitNum); 
}

UINT8 read_reg(UINT8 addr) 
{
	return *((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER)));
}

UINT8 read_reg_bit(UINT8 addr, UINT8 bitNum)
{
	return *((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER))) & (1<<bitNum); 
}


void write_eeprom(UINT8 addr, UINT8 data) {
	/* default to write eeprom and restore interrupts */
	write_eeprom_restore(addr, data, (UINT8)1);
}

void write_eeprom_restore(UINT8 addr, UINT8 data, UINT8 restore_interrupts)
{
	/* write byte to eeprom addr */

	/* wait for completion of previous write */
	while ( (read_reg(EECR) & EEPE) )
		;

	disable_interrupt();		/* prevent interrupts amd wrote cycle failure */

	write_reg(EEAR, addr);		/* set addr register */
	write_reg(EEDR, data);		/* write data register */
	write_reg(EECR, EEMPE);		/* enable write */
	write_reg(EECR, EEPE);		/* write eepom */

	if (restore_interrupts) {
		enable_interrupt();		/* global interrupts */
	}
}

UINT8 read_eeprom(UINT8 addr) 
{
	/* read byte to eeprom addr - returns -1 if FAILED to read; otherwise, byte value */
	
	/* wait for completion of previous write */
	while ( (read_reg(EECR) & EEPE) )
		;
		
	write_reg(EEAR, addr);		/* set addr register */
	write_reg(EECR, EERE);		/* enable eeprom read */

	return read_reg(EEDR);		/* read data from data register */
}



