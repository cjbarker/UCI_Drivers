/* ********************************************* *
 * LAB 4 - Writing Portable Device Drivers       *
 *                                               *
 * Program is a Serial to EEPROM storage device  *
 * with playback characteristcs.  Also includes  *
 * Lab3's timer ISR for LED display/toggle.      *
 *                                               *
 * Reads keys from Spare RS232 and records them  *
 * to the EEPROM.  Additionally, provides LED    *
 * swtich cycling and toggling. Toggles the      *
 * corresponding LED when the switch is          *
 * presessed; otherwise, cycles through all      *
 * LEDs with pattern (rinse and repeat).         *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#include "labport.h"
#include "labapi.h"
#include "labreg.h"

#define TOTAL_LEDS 	8
#define LED_DELAY 	15

volatile UINT32 gCurrLed = 0;		/* current active LED to light */
volatile UINT32 gTimeCounter = 0; 	/* used for timer to achieve 1Hz */

BOOL switchPushed(void)
{
	/* denotes whether or not a LED switch was pushed */

	volatile UINT8 switchesRegVal = 0;

	switchesRegVal = readReg(PIND);	/* read input from PORTD */

	/* check if any switch pressed */
	for (int i=0; i < TOTAL_LEDS; i++) 
	{
		if (switchesRegVal == (UINT8) ~(1 << i)) {
			return TRUE;
		}
	}

	return FALSE;
}

void initTimer(void)
{
	/* Initialize Timer/Counter 0 (internal system clock) for interrupt */
	writeReg(TCCR0A, 0);			/* normal operation mode */
	writeReg(TCCR0B, CS02 | CS00);	/* clk(I/O)/1024 (from pre-scaler) */
	writeReg(TCNT0, 256-LED_DELAY);	/* initialize counter value */
	writeReg(TIMSK0, TOIE0);		/* enable interrupt */

	enable_interrupt();				/* global interrupts */
}

void timerHandler(void)
{
	/* Timer 0 overlow interrupt */
	gTimeCounter++;

	/* reset LED and timers when switched pushed */	
	if (switchPushed()) {
		writeReg(PORTB, 0xff);		/* turn off LEDs */
		gTimeCounter = LED_DELAY;	
		gCurrLed = 0;
	}

	enable_interrupt();				/* global interrupts */
}

void __vector_23 (void) 
{ 
	/* timer 0 overflow */ 
	timerHandler();
}

int main(void)
{
	initTimer();			/* setup and start timer */

	writeReg(DDRB, 0xff);	/* enable output mode for all pins - control LEDs on PORTB */
	writeReg(DDRD, 0);		/* enable input mode for all pins on PORTD */
	writeReg(PORTB, 0xff);	/* turn off LEDs */

	/* wait for interrupt to trigger and check input switches */
	while(1)
	{
		/* sequentially toggle on current LED when delay met */
		if (gTimeCounter >= LED_DELAY) 
		{
			gTimeCounter = 0;

			writeReg(PORTB, (UINT8) ~(1 << gCurrLed));	/* turn on LED */

			gCurrLed++;
			if (gCurrLed >= TOTAL_LEDS) {
				gCurrLed = 0;
			}
		}
	}

	return(0);
}
