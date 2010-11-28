/* ********************************************* *
 * Writing Portable Device Drivers               *
 *                                               *
 * Header file for API function prototypes.      *
 *                                               *
 * By: Clifton (CJ) Barker                       *
 * ********************************************* */

#ifndef LABAPI_H

#define LABAPI_H

#include "labport.h"

/* Register Writes */
void write_reg(UINT8 addr, UINT8 data);
void write_reg_bit(UINT8 addr, UINT8 bitNum);

/* Register Reads */
UINT8 read_reg(UINT8 addr);
UINT8 read_reg_bit(UINT8 addr, UINT8 bitNum);

/* EEPROM Access */
void write_eeprom(UINT8 addr, UINT8 data);
void write_eeprom_restore(UINT8 addr, UINT8 data, UINT8 restore_interrupts);
UINT8 read_eeprom(UINT8 addr);

#endif
