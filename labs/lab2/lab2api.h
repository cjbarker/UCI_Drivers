/* ********************************************* *
 * LAB 2 - Writing Portable Device Drivers       *
 *                                               *
 * Header file for API function prototypes.      *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#ifndef LAB2API_H

#define LAB2API_H

#include "lab2port.h"

void writeReg(UINT8 addr, UINT8 value);

void writeRegBit(UINT8 addr, UINT8 bitNum);

#endif
