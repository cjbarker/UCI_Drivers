/* ********************************************* *
 * LAB 3 - Writing Portable Device Drivers       *
 *                                               *
 * Header file for API function prototypes.      *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#ifndef LABAPI_H

#define LABAPI_H

#include "labport.h"

/* Register Writes */
void writeReg(UINT8 addr, UINT8 value);
void writeRegBit(UINT8 addr, UINT8 bitNum);

/* Register Reads */
UINT8 readReg(UINT8 addr);
UINT8 readRegBit(UINT8 addr, UINT8 bitNum);

#endif
