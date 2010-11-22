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

#define FOSC 1000000		           					/* oscillator-frequency in Hz */
#define UART_BAUD_RATE 9600								/* Bits Per Second */
#define UART_BAUD_CALC(UART_BAUD_RATE,FOSC) ((FOSC)/((UART_BAUD_RATE)*16l)-1)

volatile enum STATES { stopped=0, started } gRecState;	/* UART recording state */
volatile UINT32 g_curr_led = 0;							/* current active LED to light */
volatile UINT32 g_time_counter = 0; 					/* used for timer to achieve 1Hz */

BOOL switch_pushed(void)
{
	/* denotes whether or not a LED switch was pushed */

	volatile UINT8 switch_reg_val = 0;

	switch_reg_val = read_reg(PIND);	/* read input from PORTD */

	/* check if any switch pressed */
	for (int i=0; i < TOTAL_LEDS; i++) 
	{
		if (switch_reg_val == (UINT8) ~(1 << i)) {
			return TRUE;
		}
	}

	return FALSE;
}

void init_timer(void)
{
	/* Initialize Timer/Counter 0 (internal system clock) for interrupt */
	write_reg(TCCR0A, 0);			/* normal operation mode */
	write_reg(TCCR0B, CS02 | CS00);	/* clk(I/O)/1024 (from pre-scaler) */
	write_reg(TCNT0, 256-LED_DELAY);	/* initialize counter value */
	write_reg(TIMSK0, TOIE0);		/* enable interrupt */

	enable_interrupt();				/* global interrupts */
}

void init_usart(void) 
{
	/* Initialize normal asynchronous interrupt driven USART #0 Receiver */
	gRecState = stopped;

	/* enable complete interrupts, data empty interrupt, and receiver & trx mode */
	write_reg(UCSR0B, RXCIEn | TXCIEn | UDRIEn  | RXENn | TXENn);	

	/* set frame format: 8 bit character size for frame used by transmitter and receiver with 2 stop bit */
	write_reg(UCSR0C, USBSn| UCSZn1 | UCSZn0);								

	/* Baud Rate */		
	write_reg(UBRR0H, (UINT8)UART_BAUD_CALC(UART_BAUD_RATE,FOSC)>>8);
	write_reg(UBRR0L, (UINT8)UART_BAUD_CALC(UART_BAUD_RATE,FOSC));

	enable_interrupt();				/* global interrupts */
}

void timer_handler(void)
{
	/* Timer 0 overlow interrupt */
	g_time_counter++;

	/* reset LED and timers when switched pushed */	
	if (switch_pushed()) {
		write_reg(PORTB, 0xff);		/* turn off LEDs */
		g_time_counter = LED_DELAY;	
		g_curr_led = 0;
	}

	enable_interrupt();				/* global interrupts */
}

void usart_rx_handler(void)
{
	/* USART0 receive complete interrupt */

	/* read data from buffer */
	volatile UINT8 result;
	write_reg(UDR0, result);
	

	/* 
	TODO
	1) Convert bytes to integer ASCII encoding then ASCII character
	2) See if cntrl start or stop recording received - update gRecState
	3) Handle start/stop accordingly if exists if not and recording store characters to EEPROM
	4) re-enable interrupts
	*/

	enable_interrupt();				/* global interrupts */
}

void __vector_23 (void) 
{ 
	/* timer 0 overflow */ 
	timer_handler();
}

void __vector_26 (void) 
{ 
	/* USART0 receive complete */ 
	usart_rx_handler();
}

int main(void)
{
	init_timer();			/* setup and start timer */
	init_usart();			/* setup USART */

	write_reg(DDRB, 0xff);	/* enable output mode for all pins - control LEDs on PORTB */
	write_reg(DDRD, 0);		/* enable input mode for all pins on PORTD */
	write_reg(PORTB, 0xff);	/* turn off LEDs */

	/* wait for interrupts to trigger (timer or USART handlers) */
	while(1)
	{
		/* sequentially toggle on current LED when delay met */
		if (g_time_counter >= LED_DELAY) 
		{
			g_time_counter = 0;

			write_reg(PORTB, (UINT8) ~(1 << g_curr_led));	/* turn on LED */

			g_curr_led++;
			if (g_curr_led >= TOTAL_LEDS) {
				g_curr_led = 0;
			}
		}
	}

	return(0);
}
