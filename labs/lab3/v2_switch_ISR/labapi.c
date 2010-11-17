/* ********************************************* *
 * LAB 3 - Writing Portable Device Drivers       *
 *                                               *
 * Implements PORT functions.                     *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#include "labport.h"
#include "labapi.h"

void writeReg(UINT8 addr, UINT8 value) {
	*((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER))) = value;
}

void writeRegBit(UINT8 addr, UINT8 bitNum)
{
	/* individual register bit masking */
	writeReg(addr, 0);
	*((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER))) |= (1<<bitNum); 
}

UINT8 readReg(UINT8 addr) 
{
	return *((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER)));
}

UINT8 readRegBit(UINT8 addr, UINT8 bitNum)
{
	return *((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER))) & (1<<bitNum); 
}



