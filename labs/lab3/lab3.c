/* ********************************************* *
 * LAB 3 - Writing Portable Device Drivers       *
 *                                               *
 * Program utilizes interrupts for reading       *
 * switches next to LEDs on ATMEGA board.        *
 * Toggles the corresponding LED when the switch *
 * is presessed; otherwise, cycles through all   *
 * LEDs with pattern (rinse and repeat).         *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#include "labport.h"
#include "labapi.h"
#include "labreg.h"

#define TOTAL_LEDS 	8
#define LED_DELAY 	15

volatile UINT32 CURR_LED = 0;		/* current active LED to light */
volatile UINT32 TIME_COUNTER = 0; 	/* used for timer to achieve 1Hz */

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

void interruptHandler(void)
{
	/* Timer 0 overlow interrupt */
	TIME_COUNTER++;

	/* reset LED and timers when switched pushed */	
	if (switchPushed()) {
		writeReg(PORTB, 0xff);		/* turn off LEDs */
		TIME_COUNTER = LED_DELAY;	
		CURR_LED = 0;
	}

	enable_interrupt();				/* global interrupts */
}

void __vector_23 (void) 
{ 
	/* timer 0 overflow */ 
	interruptHandler();
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
		if (TIME_COUNTER >= LED_DELAY) 
		{
			TIME_COUNTER = 0;

			writeReg(PORTB, (UINT8) ~(1 << CURR_LED));	/* turn on LED */

			CURR_LED++;
			if (CURR_LED >= TOTAL_LEDS) {
				CURR_LED = 0;
			}
		}
	}

	return(0);
}
