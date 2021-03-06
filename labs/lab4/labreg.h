/* ********************************************* *
 * Writing Portable Device Drivers               *
 *                                               *
 * Header file for ATMEGA2560 registers          *
 * (hardware represented to software)            *
 * Includes register definitions for following:  *
 * Timers, UART, EEPROM, and I/O Ports           *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#ifndef LABREG_H

#define LABREG_H

/* ***************************************************
 * ATMEGA2560 - Universal Asych Receiver/Transmitter *
 * ***************************************************/
/* UART translates data between parallel and serial forms
 * serial comm. over serial port */

/* USART I/O Data Register n */

/* USART 0 */ 
#define UDR0    0xA6	/* memory location */
#define UCSR0A  0xA0	/* memory location */
#define UCSR0B  0xA1	/* memory location */
#define UCSR0C  0xA2	/* memory location */
#define UBRR0L  0xA4	/* memory location */
#define UBRR0H  0xA5	/* memory location */

/* USART 1 */
#define UDR1    0xAE	/* memory location */
#define UCSR1A  0xA8	/* memory location */
#define UCSR1B  0xA9	/* memory location */
#define UCSR1C  0xAA	/* memory location */
#define UBRR1L  0xAC	/* memory location */
#define UBRR1H  0xAD	/* memory location */

/* USART 2 */
#define UDR2    0xB6	/* memory location */
#define UCSR2A  0xB0	/* memory location */
#define UCSR2B  0xB1	/* memory location */
#define UCSR2C  0xB2	/* memory location */
#define UBRR2L  0xB4	/* memory location */
#define UBRR2H  0xB5	/* memory location */

/* USART 3 */
#define UDR3    0x116	/* memory location */
#define UCSR3A  0x110	/* memory location */
#define UCSR3B  0x111	/* memory location */
#define UCSR3C  0x112	/* memory location */
#define UBRR3L  0x114	/* memory location */
#define UBRR3H  0x115	/* memory location */

/* USART Control and Status Register A */
#define	RXCn	(1<<7)	/* R */
#define TXCn	(1<<6)	/* R/W */
#define UDREn	(1<<5)	/* R */
#define FEn		(1<<4)	/* R */
#define DORn	(1<<3)	/* R */
#define UPEn	(1<<2)	/* R */
#define U2Xn	(1<<1)	/* R/W */
#define MPCMn	(1<<0)	/* R/W */

/* USART Control and Status Register B */
#define RXCIEn	(1<<7)	/* R/W */
#define TXCIEn	(1<<6)	/* R/W */
#define UDRIEn	(1<<5)	/* R/W */
#define RXENn	(1<<4)	/* R/W */
#define TXENn	(1<<3)	/* R/W */
#define UCSZn2	(1<<2)	/* R/W */
#define RXB8n	(1<<1)	/* R */
#define TXB8n	(1<<0)	/* R/W */


/* USART Control and Status Register n C */
#define UMSELn1	(1<<7)	/* R/W */
#define UMSELn0	(1<<6)	/* R/W */
#define UPMn1	(1<<5)	/* R/W */
#define UPMn0	(1<<4)	/* R/W */
#define USBSn	(1<<3)	/* R/W */
#define UCSZn1	(1<<2)	/* R/W */
#define UCSZn0	(1<<1)	/* R/W */
#define UCPOLn	(1<<0)	/* R/W */

/* USART Baud Rate Registers */
#define UBRR11	(1<<11)
#define UBRR10	(1<<10)
#define UBRR9	(1<<9)
#define UBRR8	(1<<8)
#define UBRR7	(1<<7)
#define UBRR6	(1<<6)
#define UBRR5	(1<<5)
#define UBRR4	(1<<4)
#define UBRR3	(1<<3)
#define UBRR2	(1<<2)
#define UBRR1	(1<<1)
#define UBRR0	(1<<0)

 
/* ******************************* *
 * ATMEGA2560 - I/O Port Registers *
 * ******************************* */

/* Port B data register - how we read or write registers*/
#define PORTB	0x05	/* memory location */
#define PORTB7	(1<<7)	/* R/W */
#define PORTB6	(1<<6)	/* R/W */
#define PORTB5 	(1<<5)	/* R/W */
#define PORTB4 	(1<<4)	/* R/W */
#define PORTB3 	(1<<3)	/* R/W */
#define PORTB2 	(1<<2)	/* R/W */
#define PORTB1 	(1<<1)	/* R/W */
#define PORTB0 	(1<<0)	/* R/W */

/* Port C data register - how we read or write registers*/
#define PORTC	0x08	/* memory location */
#define PORTC7	(1<<7)	/* R/W */
#define PORTC6	(1<<6)	/* R/W */
#define PORTC5 	(1<<5)	/* R/W */
#define PORTC4 	(1<<4)	/* R/W */
#define PORTC3 	(1<<3)	/* R/W */
#define PORTC2 	(1<<2)	/* R/W */
#define PORTC1 	(1<<1)	/* R/W */
#define PORTC0 	(1<<0)	/* R/W */

/* Port D data register - how we read or write registers*/
#define PORTD	0x0B	/* memory location */
#define PORTD7	(1<<7)	/* R/W */
#define PORTD6	(1<<6)	/* R/W */
#define PORTD5 	(1<<5)	/* R/W */
#define PORTD4 	(1<<4)	/* R/W */
#define PORTD3 	(1<<3)	/* R/W */
#define PORTD2 	(1<<2)	/* R/W */
#define PORTD1 	(1<<1)	/* R/W */
#define PORTD0 	(1<<0)	/* R/W */

/* Port B data direction register - determines if input or output */
#define DDRB	0x04	/* memory location */
#define DDB7	(1<<7)	/* R/W */
#define DDB6	(1<<6)	/* R/W */
#define DDB5 	(1<<5)	/* R/W */
#define DDB4 	(1<<4)	/* R/W */
#define DDB3 	(1<<3)	/* R/W */
#define DDB2 	(1<<2)	/* R/W */
#define DDB1 	(1<<1)	/* R/W */
#define DDB0 	(1<<0)	/* R/W */

/* Port C data direction register - determines if input or output */
#define DDRC	0x07	/* memory location */
#define DDC7	(1<<7)	/* R/W */
#define DDC6	(1<<6)	/* R/W */
#define DDC5 	(1<<5)	/* R/W */
#define DDC4 	(1<<4)	/* R/W */
#define DDC3 	(1<<3)	/* R/W */
#define DDC2 	(1<<2)	/* R/W */
#define DDC1 	(1<<1)	/* R/W */
#define DDC0 	(1<<0)	/* R/W */

/* Port D data direction register - determines if input or output */
#define DDRD	0x0A	/* memory location */
#define DDD7	(1<<7)	/* R/W */
#define DDD6	(1<<6)	/* R/W */
#define DDD5 	(1<<5)	/* R/W */
#define DDD4 	(1<<4)	/* R/W */
#define DDD3 	(1<<3)	/* R/W */
#define DDD2 	(1<<2)	/* R/W */
#define DDD1 	(1<<1)	/* R/W */
#define DDD0 	(1<<0)	/* R/W */

/* PIN B input pins address - when we read the value (make it work) */
#define PINB	0x03	/* memory location */
#define PINB7	(1<<7)	/* R/W */
#define PINB6	(1<<6)	/* R/W */
#define PINB5 	(1<<5)	/* R/W */
#define PINB4 	(1<<4)	/* R/W */
#define PINB3 	(1<<3)	/* R/W */
#define PINB2 	(1<<2)	/* R/W */
#define PINB1 	(1<<1)	/* R/W */
#define PINB0 	(1<<0)	/* R/W */

/* PIN C input pins address - when we read the value (make it work) */
#define PINC	0x06	/* memory location */
#define PINC7	(1<<7)	/* R/W */
#define PINC6	(1<<6)	/* R/W */
#define PINC5 	(1<<5)	/* R/W */
#define PINC4 	(1<<4)	/* R/W */
#define PINC3 	(1<<3)	/* R/W */
#define PINC2 	(1<<2)	/* R/W */
#define PINC1 	(1<<1)	/* R/W */
#define PINC0 	(1<<0)	/* R/W */

/* PIN D input pins address - when we read the value (make it work) */
#define PIND	0x09	/* memory location */
#define PIND7	(1<<7)	/* R/W */
#define PIND6	(1<<6)	/* R/W */
#define PIND5 	(1<<5)	/* R/W */
#define PIND4 	(1<<4)	/* R/W */
#define PIND3 	(1<<3)	/* R/W */
#define PIND2 	(1<<2)	/* R/W */
#define PIND1 	(1<<1)	/* R/W */
#define PIND0 	(1<<0)	/* R/W */

/* ******************************* *
 * ATMEGA2560 - EEPROM definitions * 
 * ******************************* */
/* Note: indirect register access 
 * take one register and write address to it 
 * (results in two registers) */

/* EEPROM address register high byte */
/* Note - Bits 15:12 are reserved and always read as zero */
#define EEARH	0x22	/* memory location */
#define EEAR11	(1<<11)	/* R/W */
#define EEAR10	(1<<10)	/* R/W */
#define EEAR9	(1<<9)	/* R/W */
#define EEAR8	(1<<8)	/* R/W */

/* EEPROM address register low byte */
#define EEARL	0x21	/* memory location */
#define EEAR7	(1<<7)	/* R/W */
#define EEAR6	(1<<6)	/* R/W */
#define EEAR5	(1<<5)	/* R/W */
#define EEAR4	(1<<4)	/* R/W */
#define EEAR3	(1<<3)	/* R/W */
#define EEAR2	(1<<2)	/* R/W */
#define EEAR1	(1<<1)	/* R/W */
#define EEAR0	(1<<0)	/* R/W */

#define EEAR	EEARL	/* memory location */

/* EEPROM data register (data to be written/read to/from EEPROM) */
/* NOTE - BIG ENDIAN ORDER */
#define EEDR	0x20	/* memory location */
#define EEDRMSB (1<<7)	/* R/W */
#define EEDRLSB (1<<0)  /* R/W */

/* EEPROM control register () */
/* Note - Bits 7:6 are reserved and always read as zero */
#define EECR	0x1F	/* memory location */
#define EEPM1	(1<<5)	/* R/W */
#define EEPM0	(1<<4)	/* R/W */
#define EEPM0	(1<<4)	/* R/W */
#define EERIE	(1<<3)	/* R/W */
#define EEMPE	(1<<2)	/* R/W */
#define EEPE	(1<<1)	/* R/W */
#define EERE	(1<<0)	/* R/W */


/* ********************************** *
 * ATMEGA2560 - Interrupt definitions * 
 * ********************************** */

/* AVR Status Register */
#define SREG	0x3F	/* memory location */
#define I		(1<<7)	/* R/W */
#define T		(1<<6)	/* R/W */
#define H		(1<<5)	/* R/W */
#define S		(1<<4)	/* R/W */
#define V		(1<<3)	/* R/W */
#define N		(1<<2)	/* R/W */
#define Z		(1<<1)	/* R/W */
#define C		(1<<0)	/* R/W */

/* External Interrupt */
#define EIMSK	0x1D	/* memory location */
#define INT7	(1<<7)	/* R/W */
#define INT6	(1<<6)	/* R/W */
#define INT5	(1<<5)	/* R/W */
#define INT4	(1<<4)	/* R/W */
#define INT3	(1<<3)	/* R/W */
#define INT2	(1<<2)	/* R/W */
#define INT1	(1<<1)	/* R/W */
#define INT0	(1<<0)	/* R/W */

#define EICRA   0x49	/* memory location */
#define ISC31	(1<<7)	/* R/W */
#define ISC30	(1<<6)	/* R/W */
#define ISC21	(1<<5)	/* R/W */
#define ISC20	(1<<4)	/* R/W */
#define ISC11	(1<<3)	/* R/W */
#define ISC10	(1<<2)	/* R/W */
#define ISC01	(1<<1)	/* R/W */
#define ISC00	(1<<0)	/* R/W */

#define EICRB   0x4A	/* memory location */
#define ISC71	(1<<7)	/* R/W */
#define ISC70	(1<<6)	/* R/W */
#define ISC61	(1<<5)	/* R/W */
#define ISC60	(1<<4)	/* R/W */
#define ISC51	(1<<3)	/* R/W */
#define ISC50	(1<<2)	/* R/W */
#define ISC41	(1<<1)	/* R/W */
#define ISC40	(1<<0)	/* R/W */
	

/* ****************************** *
 * ATMEGA2560 - Timer definitions * 
 * ****************************** */

/* Watchdog Timer Control Register */
#define WDTCSR	0x40	/* memory location */
#define WDIF	(1<<7)	/* R/W */
#define WDIE	(1<<6)	/* R/W */
#define WDP3	(1<<5)	/* R/W */
#define WDCE	(1<<4)	/* R/W */
#define WDE		(1<<3)	/* R/W */
#define WDP2	(1<<2)	/* R/W */
#define WDP1	(1<<1)	/* R/W */
#define WDP0	(1<<0)	/* R/W */

/* Timer/Counter 0 Control Register A */
#define TCCR0A	0x24	/* memory location */
#define COM0A1	(1<<7)	/* R/W */
#define COM0A0	(1<<6)	/* R/W */
#define COM0B1	(1<<5)	/* R/W */
#define COM0B0	(1<<4)	/* R/W */
#define WGM01	(1<<1)	/* R/W */
#define WGM00	(1<<0)	/* R/W */

/* Timer/Counter 0 Control Register B */
#define TCCR0B	0x25	/* memory location */
#define FOC0A	(1<<7)	/* R/W */
#define FOC0B	(1<<6)	/* R/W */
#define WGM02	(1<<3)	/* R/W */
#define CS02	(1<<2)	/* R/W */
#define CS01	(1<<1)	/* R/W */
#define CS00	(1<<0)	/* R/W */

/* Timer/Counter Register */
#define TCNT0	0x26	/* memory location */

/* Timer/Counter Interrupt Mask Register */
#define TIMSK0	0x4E	/* memory location */
#define OCF0B	(1<<2)	/* R/W */
#define OCF0A	(1<<1)	/* R/W */
#define TOV0	(1<<0)	/* R/W */

/* Timer/Counter 0 Interrupt Flag Register */
#define TIFR0	0x15	/* memory location */
#define OCIE0B	(1<<2)	/* R/W */
#define OCIE0A	(1<<1)	/* R/W */
#define TOIE0	(1<<0)	/* R/W */

/* Timer/Counter 1 Control Register A */
#define TCCR1A	0x60	/* memory location */
#define COM1A1	(1<<7)	/* R/W */
#define COM1A0	(1<<6)	/* R/W */
#define COM1B1	(1<<5)	/* R/W */
#define COM1B0	(1<<4)	/* R/W */
#define COM1C1	(1<<3)	/* R/W */
#define COM1C0	(1<<2)	/* R/W */
#define WGM11	(1<<1)	/* R/W */
#define WGM10	(1<<0)	/* R/W */

/* Timer/Counter 3 Control Register A */
#define TCCR3A	0x70	/* memory location */
#define COM3A1	(1<<7)	/* R/W */
#define COM3A0	(1<<6)	/* R/W */
#define COM3B1	(1<<5)	/* R/W */
#define COM3B0	(1<<4)	/* R/W */
#define COM3C1	(1<<3)	/* R/W */
#define COM3C0	(1<<2)	/* R/W */
#define WGM31	(1<<1)	/* R/W */
#define WGM30	(1<<0)	/* R/W */

/* Timer/Counter 4 Control Register A */
#define TCCR4A	0x80	/* memory location */
#define COM4A1	(1<<7)	/* R/W */
#define COM4A0	(1<<6)	/* R/W */
#define COM4B1	(1<<5)	/* R/W */
#define COM4B0	(1<<4)	/* R/W */
#define COM4C1	(1<<3)	/* R/W */
#define COM4C0	(1<<2)	/* R/W */
#define WGM41	(1<<1)	/* R/W */
#define WGM40	(1<<0)	/* R/W */

/* Timer/Counter 5 Control Register A */
#define TCCR5A	0x100	/* memory location */
#define COM5A1	(1<<7)	/* R/W */
#define COM5A0	(1<<6)	/* R/W */
#define COM5B1	(1<<5)	/* R/W */
#define COM5B0	(1<<4)	/* R/W */
#define COM5C1	(1<<3)	/* R/W */
#define COM5C0	(1<<2)	/* R/W */
#define WGM51	(1<<1)	/* R/W */
#define WGM50	(1<<0)	/* R/W */

/* Timer/Counter 1 Control Register B */
#define TCCR1B	0x61	/* memory location */
#define ICNC1	(1<<7)	/* R/W */
#define ICES1	(1<<6)	/* R/W */
#define WGM13	(1<<4)	/* R/W */
#define WGM12	(1<<3)	/* R/W */
#define CS12	(1<<2)	/* R/W */
#define CS11	(1<<1)	/* R/W */
#define CS10	(1<<0)	/* R/W */

/* Timer/Counter 3 Control Register B */
#define TCCR3B	0x71	/* memory location */
#define ICNC3	(1<<7)	/* R/W */
#define ICES3	(1<<6)	/* R/W */
#define WGM33	(1<<4)	/* R/W */
#define WGM32	(1<<3)	/* R/W */
#define CS32	(1<<2)	/* R/W */
#define CS31	(1<<1)	/* R/W */
#define CS30	(1<<0)	/* R/W */

/* Timer/Counter 4 Control Register B */
#define TCCR4B	0x81	/* memory location */
#define ICNC4	(1<<7)	/* R/W */
#define ICES4	(1<<6)	/* R/W */
#define WGM43	(1<<4)	/* R/W */
#define WGM42	(1<<3)	/* R/W */
#define CS42	(1<<2)	/* R/W */
#define CS41	(1<<1)	/* R/W */
#define CS40	(1<<0)	/* R/W */

/* Timer/Counter 5 Control Register B */
#define TCCR5B	0x101	/* memory location */
#define ICNC5	(1<<7)	/* R/W */
#define ICES5	(1<<6)	/* R/W */
#define WGM53	(1<<4)	/* R/W */
#define WGM52	(1<<3)	/* R/W */
#define CS52	(1<<2)	/* R/W */
#define CS51	(1<<1)	/* R/W */
#define CS50	(1<<0)	/* R/W */

/* Timer/Counter 1 Control Register C */
#define TCCR1C	0x62	/* memory location */
#define FOC1A	(1<<7)	/* W */
#define FOC1B	(1<<6)	/* W */
#define FOC1C	(1<<5)	/* W */

/* Timer/Counter 3 Control Register C */
#define TCCR3C	0x72	/* memory location */
#define FOC3A	(1<<7)	/* W */
#define FOC3B	(1<<6)	/* W */
#define FOC3C	(1<<5)	/* W */

/* Timer/Counter 4 Control Register C */
#define TCCR4C	0x82	/* memory location */
#define FOC4A	(1<<7)	/* W */
#define FOC4B	(1<<6)	/* W */
#define FOC4C	(1<<5)	/* W */

/* Timer/Counter 5 Control Register C */
#define TCCR5C	0x102	/* memory location */
#define FOC5A	(1<<7)	/* W */
#define FOC5B	(1<<6)	/* W */
#define FOC5C	(1<<5)	/* W */

/* Timer/Counter 1 */
#define TCNT1H	0x65	/* memory location */
#define TCNT1L	0x64	/* memory location */

/* Timer/Counter 3 */
#define TCNT3H	0x75	/* memory location */
#define TCNT3L	0x74	/* memory location */

/* Timer/Counter 4 */
#define TCNT4H	0x85	/* memory location */
#define TCNT4L	0x84	/* memory location */

/* Timer/Counter 5 */
#define TCNT5H	0x105	/* memory location */
#define TCNT5L	0x104	/* memory location */

/* Timer/Counter 1 Interrupt Mask Register */
#define TIMSK1	0x4F	/* memory location */
#define ICIE1	(1<<5>	/* R/W */
#define OCIE1C	(1<<3)	/* R/W */
#define OCIE1B	(1<<2)	/* R/W */
#define OCIE1A	(1<<1)	/* R/W */
#define TOIE1	(1<<0)	/* R/W */

/* Timer/Counter 3 Interrupt Mask Register */
#define TIMSK3	0x51	/* memory location */
#define ICIE3	(1<<5>	/* R/W */
#define OCIE3C	(1<<3)	/* R/W */
#define OCIE3B	(1<<2)	/* R/W */
#define OCIE3A	(1<<1)	/* R/W */
#define TOIE3	(1<<0)	/* R/W */

/* Timer/Counter 4 Interrupt Mask Register */
#define TIMSK4	0x52	/* memory location */
#define ICIE4	(1<<5>	/* R/W */
#define OCIE4C	(1<<3)	/* R/W */
#define OCIE4B	(1<<2)	/* R/W */
#define OCIE4A	(1<<1)	/* R/W */
#define TOIE4	(1<<0)	/* R/W */

/* Timer/Counter 5 Interrupt Mask Register */
#define TIMSK5	0x53	/* memory location */
#define ICIE5	(1<<5>	/* R/W */
#define OCIE5C	(1<<3)	/* R/W */
#define OCIE5B	(1<<2)	/* R/W */
#define OCIE5A	(1<<1)	/* R/W */
#define TOIE5	(1<<0)	/* R/W */

/* Timer/Counter 1 Interrupt Flag Register */
#define TIFR1	0x16	/* memory location */
#define ICF1	(1<<5>	/* R/W */
#define OCF1C	(1<<3)	/* R/W */
#define OCF1B	(1<<2)	/* R/W */
#define OCF1A	(1<<1)	/* R/W */
#define TOV1	(1<<0)	/* R/W */

/* Timer/Counter 3 Interrupt Flag Register */
#define TIFR3	0x18	/* memory location */
#define ICF3	(1<<5>	/* R/W */
#define OCF3C	(1<<3)	/* R/W */
#define OCF3B	(1<<2)	/* R/W */
#define OCF3A	(1<<1)	/* R/W */
#define TOV3	(1<<0)	/* R/W */

/* Timer/Counter 4 Interrupt Flag Register */
#define TIFR4	0x19	/* memory location */
#define ICF4	(1<<5>	/* R/W */
#define OCF4C	(1<<3)	/* R/W */
#define OCF4B	(1<<2)	/* R/W */
#define OCF4A	(1<<1)	/* R/W */
#define TOV4	(1<<0)	/* R/W */

/* Timer/Counter 5 Interrupt Flag Register */
#define TIFR5	0x1A	/* memory location */
#define ICF5	(1<<5>	/* R/W */
#define OCF5C	(1<<3)	/* R/W */
#define OCF5B	(1<<2)	/* R/W */
#define OCF5A	(1<<1)	/* R/W */
#define TOV5	(1<<0)	/* R/W */

/* Timer/Counter2 Interrupt Mask Register */
#define TIMSK2	0x50	/* memory location */
#define OCIE2B	(1<<2)	/* R/W */
#define OCIE2A	(1<<1)	/* R/W */
#define TOIE2	(1<<0)	/* R/W */

/* Timer/Counter2 Interrupt Flag Register */
#define TIFR2	0x17	/* memory location */
#define OCF2B	(1<<2)	/* R/W */
#define OCF2A	(1<<1)	/* R/W */
#define TOV2	(1<<0)	/* R/W */

/* General Timer/Counter Control Register */
#define GTCCR	0x23	/* memory location */
#define TSM		(1<<7)	/* R/W */
#define PSRASY	(1<<1)	/* R/W */
#define PSRSYNC	(1<<0)	/* R/W */

#endif
