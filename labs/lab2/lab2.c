/* ********************************************* *
 * LAB 2 - Writing Portable Device Drivers       *
 *                                               *
 * Program is modification of Lab1 with header   *
 * definig majority of ATMEGA2560 registers.     *
 * Additionally, utilizes function for writing   *
 * entire byte to the register (no bit masking). *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#include "lab2port.h"
#include "lab2reg.h"
#include "lab2api.h"

void delay(UINT32 val)
{
	volatile UINT32 temp;
	volatile UINT32 temp2;

	for(temp = 0; temp < val; temp++) 
		for (temp2 = 0; temp2 < val; temp2 ++) ;
}

int main(void)
{
	volatile UINT8 pDDRB  = DDRB;
	volatile UINT8 pPORTB = PORTB;

	volatile UINT32 delayTime = 500;
	volatile UINT32 i;
	UINT32 minDelay = 50;

	writeReg(pDDRB, 0xff);

	while(1) 
	{
		writeReg(pPORTB, 0);
	 	delay(delayTime);
		writeReg(pPORTB, 0xff);
	 	delay(delayTime);

		/* add some more fun with sequential LED display */
		for (i=0; i < 8; i++) {
			writeRegBit(pPORTB, i);
			delay(75);
		}

		/* speed blinking up overtime */
		delayTime -= minDelay;
		if (delayTime < minDelay) {
			delayTime = minDelay;
		}
	}

	return(0);
}
