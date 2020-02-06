/*
 * mod_lcd.h
 *
 *  Created on: Mar 7, 2014
 *      Author: wondartinf-01
 */

#ifndef MOD_LCD_H_
#define MOD_LCD_H_


#include <stdint.h>
#include "../mod_user_defs.h"
#include "mod_core.h"
#include "mod_nostdio.h"


void lcdInit();
void lcdGotoxy( uint8_t x, uint8_t y);
void lcdPuts( char message []);
void lcdPrintInt16(uint16_t varin);
void lcdPrintInt32(uint32_t varin);
void lcdPrintFloat(float varin,uint8_t FracDigits);

#define lcdPrintText(x) lcdPuts(x)

void lcdEnaPulse(void);
void lcdClearPort(void);
void lcdPut4bitLsb(uint8_t w);
void lcdPut4bitMsb(uint8_t w);
void lcdCmd(uint8_t w);
void lcdPutc(uint8_t w);
void lcdClear(void);
void lcdCursorOn(void);
void lcdCursorOff(void);
void lcdScreenOff(void);
void lcdScreenOn(void);
void lcdBlinkCharOn(void);
void lcdLeftRot(uint8_t cnt);
void lcdRightRot(uint8_t cnt);
void lcdCursorRight(uint8_t cnt);
void lcdCursorLeft(uint8_t cnt);
void lcdCursor2Home();
void lcdBlink(uint8_t cnt);
void cursor_back_lcd(uint8_t cnt);
void lcdClearL1(void);
void lcdClearL2(void);
void lcdWrite(char *varinput,...);
/*
void lcdWrite(uint16_t varin);
void lcdWrite(float varin);
*/



#endif /* MOD_LCD_H_ */
