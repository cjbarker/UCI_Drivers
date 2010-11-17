/* ********************************************* *
 * LAB 2 - Writing Portable Device Drivers       *
 *                                               *
 * Implements API functions.                     *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#include "lab2port.h"
#include "lab2api.h"

void writeReg(UINT8 addr, UINT8 value) {
	*((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER))) = value;
}

void writeRegBit(UINT8 addr, UINT8 bitNum)
{
	/* individual register bit masking */
	writeReg(addr, 0);
	*((volatile UINT8 *)((UINT32)BASE_ADDRESS + (addr*ADDR_MULTIPLIER))) |= (1<<bitNum); 
	return;
}


