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

volatile UINT32 gCurrLed = 0;		/* current active LED to light */
volatile UINT32 gTimeCounter = 0; 	/* used for timer to achieve 1Hz */

void initInterrupts(void)
{
	/* Enables external hardware interrupt and time/counter */

	/* Interrupt on high to low edge */
	writeReg(EICRA, ISC31|ISC21|ISC11|ISC01);
	writeReg(EICRB, ISC71|ISC61|ISC51|ISC41);

	/* Enable external interrupts */
	writeReg(EIMSK, 0xff);

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

	enable_interrupt();				/* global interrupts */
}

void switchHandler(void)
{
	/* reset LED and timers when switched pushed */	
	writeReg(PORTB, 0xff);		/* turn off LEDs */
	gTimeCounter = LED_DELAY;	
	gCurrLed = 0;

	enable_interrupt();				/* global interrupts */
}

void __vector_23 (void) {
	/* timer 0 overflow */ 
	timerHandler();
}

void __vector_1(void) {
	/* Input key interrupt handler */
	switchHandler();
}
void __vector_2(void) {
	/* Input key interrupt handler */
	switchHandler();
}
void __vector_3(void) {
	/* Input key interrupt handler */
	switchHandler();
}
void __vector_4(void) {
	/* Input key interrupt handler */
	switchHandler();
}
void __vector_5(void) {
	/* Input key interrupt handler */
	switchHandler();
}
void __vector_6(void) {
	/* Input key interrupt handler */
	switchHandler();
}
void __vector_7(void) {
	/* Input key interrupt handler */
	switchHandler();
}
void __vector_8(void) {
	/* Input key interrupt handler */
	switchHandler();
}

int main(void)
{
	initInterrupts();		/* setup and start timer and external interrupts */

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
