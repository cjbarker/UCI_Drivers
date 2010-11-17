/* ********************************************* *
 * Writing Portable Device Drivers               *
 *                                               *
 * Header file for porting constants and Macros. *
 * Contains OS/compiler dependencies.            *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#ifndef LABPORT_H

#define LABPORT_H

/* general definitions for un/signed integers */
#define UINT8 	unsigned char
#define INT8	signed char
#define UINT16	unsigned short
#define INT16	signed short
#define UINT32	unsigned int
#define INT32	signed int
#define BOOL	int
#define TRUE	1
#define FALSE	0

/* if each address is how far apart each register is in memory */
#define ADDR_MULTIPLIER	  1

#define BASE_ADDRESS	0	/* base address of the device */

/* global interrupt */
#define enable_interrupt()	__asm__ __volatile__ ("sei" ::)
#define disable_interrupt()	__asm__ __volatile__ ("cli" ::) 

/* vectors in AVR are hardcoded to a function by name */
extern void __vector_1(void) __attribute__ ((interrupt));
extern void __vector_2(void) __attribute__ ((interrupt));
extern void __vector_3(void) __attribute__ ((interrupt));
extern void __vector_4(void) __attribute__ ((interrupt));
extern void __vector_5(void) __attribute__ ((interrupt));
extern void __vector_6(void) __attribute__ ((interrupt));
extern void __vector_7(void) __attribute__ ((interrupt));
extern void __vector_8(void) __attribute__ ((interrupt));
extern void __vector_23(void) __attribute__ ((interrupt));


#endif
