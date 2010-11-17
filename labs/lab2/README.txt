Course: EECS497.17
Assign: Lab #2
By:     Clifton (CJ) Barker



*** Refactored ***

Created following:
1) lab2port.h - for porting constants and Macros (BASE_ADDR)
2) lab2api.h - API functions
3) lab2api.c - implemented API functions

===============================

Note: 

I had no problems getting my program to run with the new register header definitions.  I even added a little more fun with displaying the LEDs via individual bit masking.

I AM confused on how to appropriately represent the USART.  It doesn't not have a memory address and is a continous 2 byte representation.  As a result, it seems like a struct of unsigned char is the right appropriate here, but I wasn't sure.

Any feedback is more thank welcome.

Thanks!
CJ

