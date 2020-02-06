/*
 * mod_keypad.h
 *
 *  Created on: Mar 15, 2014
 *      Author: fabianrcm
 */

#ifndef MOD_KEYPAD_H_
#define MOD_KEYPAD_H_

#include "mod_core.h"
#include <stdint.h>
#include "mod_lcd.h"
#include "../mod_user_defs.h"


#define PrintToLCD 0x01
#define NoMaskToChar 0x00
#define NoPrint	  0x00
#define PRESS    0x00
#define NOPRESS  0x01

#ifdef __GNUC__
const char TecArray[16];
#endif

void keypadInit();
void keypadEnable();
void keypadDisable();
uint8_t keypadStatus();
uint8_t keypadGetc();
uint8_t keypadGetChar(uint16_t timeOut,uint8_t SendCharTo,char MaskChar);
uint8_t keypadWaitChar(uint16_t timeOut,uint8_t SendCharTo,char MaskChar);
uint8_t keypadWaitString(char *VarBuffer,uint8_t PosMem,uint8_t NumOfChars,uint16_t timeOut,uint8_t SendCharTo,char MaskChar);
uint8_t keypadGetsUntil(char *VarBuffer,uint8_t PosMem,char CharStop,uint16_t timeOut,uint8_t SendCharTo,char MaskChar);


char keypadLineGetc(void);
void keypadLineInit(void);

#endif /* MOD_KEYPAD_H_ */
