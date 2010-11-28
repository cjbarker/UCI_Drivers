/* ********************************************* *
 * LAB 4 - Writing Portable Device Drivers       *
 *                                               *
 * Program is a Serial to EEPROM storage device  *
 * with playback characteristcs.  UART IS        *
 * INTERRUPT DRIVEN.                             *
 *                                               *
 * Also includes lab3's timer ISR for LED        *
 * display/toggle.                               *
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

/* Hexadecimal for ASCII Character Set Encoding */
#define CTRL_Z	0x1A
#define CTRL_Y	0x19

#define BASE_EEPROM_ADDR 0x0

volatile enum STATES { stopped=0, recording, playback } g_rec_state;	/* UART recording state */
volatile UINT32 g_curr_led = 0;							/* current active LED to light */
volatile UINT32 g_time_counter = 0; 					/* used for timer to achieve 1Hz */
volatile UINT32 g_num_eeprom_writes = 0;				/* number of times eeprom write been called */
volatile UINT32 g_num_eeprom_reads = 0;					/* number of times eeprom read been called */
volatile UINT8 g_usart_read_buffer;						/* buffer of data read from USART */
volatile UINT8 g_data_empty_enabled = 0;				/* data register empty interrupt */

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
	g_rec_state = stopped;

	/* Baud Rate */		
	write_reg(UBRR0H, (UINT8)UART_BAUD_CALC(UART_BAUD_RATE,FOSC)>>8);
	write_reg(UBRR0L, (UINT8)UART_BAUD_CALC(UART_BAUD_RATE,FOSC));

	/* set frame format: 8 bit character size for frame used by transmitter and receiver with 2 stop bit */
	write_reg(UCSR0C, USBSn| UCSZn1 | UCSZn0);	

	/* enable interrupts receiver and trx mode */
	write_reg(UCSR0B, RXCIEn | TXCIEn | RXENn | TXENn);					

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
	g_usart_read_buffer = 0;
	g_usart_read_buffer = read_reg(UDR0);

	/* Handles Appropraite Action for State: Recording, Stop, or Playback */
	if (g_usart_read_buffer == CTRL_Z) {
		if (g_rec_state == recording) {
			g_rec_state = stopped;
		}
		else {
			g_rec_state = recording;
		}
		g_usart_read_buffer = 0;
	} 
	else if (g_usart_read_buffer == CTRL_Y && g_rec_state != playback) {
		g_rec_state = playback;
		g_usart_read_buffer = 0;
	}
	else {
		;	/* no state change result received */
	}

	if (g_usart_read_buffer && g_rec_state == recording) {
		write_eeprom(BASE_EEPROM_ADDR+g_num_eeprom_writes, g_usart_read_buffer);	/* write results to eeprom */
		g_num_eeprom_writes += 1;
	}

	/* enable data register empty interrupt with rcv and trx interrupts */
	if (!g_data_empty_enabled) {
		write_reg(UCSR0B, RXCIEn | TXCIEn | UDRIEn  | RXENn | TXENn);	
		g_data_empty_enabled = 1;
	}

	enable_interrupt();				/* global interrupts */
}

void usart_data_empty_handler(void)
{
	/* USART0 data register is empty (transmit buffer ready to receve new data) */

	if (g_rec_state == playback) 
	{
		/* Send output back via USART serial communication */
		if (g_usart_read_buffer) {
			write_reg(UDR0, g_usart_read_buffer);								/* transmit what was previously read in buffer */
			g_usart_read_buffer = 0;
		}
		else {
			write_reg(UDR0, read_eeprom(BASE_EEPROM_ADDR+g_num_eeprom_reads));	/* read EEPROM and transmit over USART */
			g_num_eeprom_reads += 1;
		}
	}

	enable_interrupt();				/* global interrupts */
}

void usart_tx_handler(void)
{
	/* USART0 transfer complete interrupt */
	/* Currently, nothing to do once transfer completes - data empty handler suffices for now */
	enable_interrupt();				/* global interrupts */
}

void __vector_23 (void) 
{ 
	/* timer 0 overflow */ 
	timer_handler();
}

void __vector_25 (void) 
{ 
	/* USART0 receive complete */ 
	usart_rx_handler();
}

void __vector_26 (void) 
{ 
	/* USART0 data register empty */
	usart_data_empty_handler();
}

void __vector_27 (void) 
{ 
	/* USART0 transfer complete */ 
	usart_tx_handler();
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
