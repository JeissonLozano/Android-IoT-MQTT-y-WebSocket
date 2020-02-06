/*
 * mod_lcd.c
 *
 *  Created on: Mar 7, 2014
 *      Author: wondartinf-01
 */

#include "mod_lcd.h"

#if defined(lcd_rs)&&defined(lcd_ena)&&defined(lcd_dato4)&&defined(lcd_dato5)&&defined(lcd_dato6)&&defined(lcd_dato7)

void lcdEnaPulse(void){
	//delay_us(1);
	pinDigHigh(lcd_ena);
	delay_cycles(3*usec);//2
	pinDigLow(lcd_ena);
	delay_cycles(3*usec);//2
}

void lcdClearPort(void){
	pinDigLow(lcd_dato4);pinDigLow(lcd_dato5);pinDigLow(lcd_dato6);pinDigLow(lcd_dato7);
}

void lcdPut4bitMsb(uint8_t w){
	uint8_t aux_lcd;
	aux_lcd=w;
	pinDigLow(lcd_dato4);
	pinDigLow(lcd_dato5);
	pinDigLow(lcd_dato6);
	pinDigLow(lcd_dato7);
	if(aux_lcd & 0x80) pinDigHigh(lcd_dato7);
	if(aux_lcd & 0x40) pinDigHigh(lcd_dato6);
	if(aux_lcd & 0x20) pinDigHigh(lcd_dato5);
	if(aux_lcd & 0x10) pinDigHigh(lcd_dato4);
}
void lcdPut4bitLsb(uint8_t w){
	uint8_t aux_lcd;
	aux_lcd=w;
	pinDigLow(lcd_dato4);
	pinDigLow(lcd_dato5);
	pinDigLow(lcd_dato6);
	pinDigLow(lcd_dato7);
	if(aux_lcd & 0x08) pinDigHigh(lcd_dato7);
	if(aux_lcd & 0x04) pinDigHigh(lcd_dato6);
	if(aux_lcd & 0x02) pinDigHigh(lcd_dato5);
	if(aux_lcd & 0x01) pinDigHigh(lcd_dato4);
}

void lcdCmd(uint8_t w){

	lcdPut4bitMsb(w);delay_cycles(20*usec);
	//delay_ms(2);
	pinDigLow(lcd_rs);//delay_cycles(2*usec);
	//delay_ms(2);
	lcdEnaPulse();//delay_cycles(2*usec);
	lcdPut4bitLsb(w);delay_cycles(20*usec);
	lcdEnaPulse();
	delay_cycles(6*usec);//delay_ms(2);
}

void lcdPutc(uint8_t w){

	lcdPut4bitMsb(w);delay_cycles(20*usec);
	//delay_ms(2);
	pinDigHigh(lcd_rs);//delay_cycles(1*usec);
	//delay_ms(2);
	lcdEnaPulse();//delay_cycles(1*usec);
	lcdPut4bitLsb(w);delay_cycles(20*usec);
	lcdEnaPulse();
	delay_cycles(6*usec);//delay_ms(2);
}

void lcdInit()
{
	/*
	 * Inicializa la LCD
	 */
	// Configure LCD Pins
	pinModeOutput(lcd_rs);
	pinModeOutput(lcd_ena);
	pinModeOutput(lcd_dato7);
	pinModeOutput(lcd_dato6);
	pinModeOutput(lcd_dato5);
	pinModeOutput(lcd_dato4);

	// Idle State
	pinDigLow(lcd_rs);
	pinDigLow(lcd_ena);
	delay_ms(15);

	// Init 4-bit LCD Mode
	pinDigHigh(lcd_ena);
	pinDigLow(lcd_dato7);
	pinDigLow(lcd_dato6);
	pinDigHigh(lcd_dato5);
	pinDigHigh(lcd_dato4);
	pinDigLow(lcd_ena);
	delay_ms(5);
	pinDigHigh(lcd_ena);
	pinDigLow(lcd_ena);
	delay_ms(1);
	pinDigHigh(lcd_ena);
	pinDigLow(lcd_ena);
	delay_ms(5);
	pinDigHigh(lcd_ena);
	pinDigLow(lcd_dato4);
	pinDigLow(lcd_ena);
	delay_ms(1);

	// LCD 4-bit Interface
	lcdCmd(0x28);

	// LCD Off Display
	lcdCmd(0x08);

	// LCD On Display
	lcdCmd(0x0C);

	// LCD Message Static with cursor auto-increment
	lcdCmd(0x06);

	// LCD Cursor Home
	lcdCmd(0x02);

	// LCD Cursor Clear
	lcdCmd(0x01);
	delay_ms(10);
}



void lcdClear(void){lcdCmd(0x01);}

void lcdCursorOn(void){lcdCmd(0x01);}

void lcdCursorOff(void){lcdCmd(0x0E);}

void lcdScreenOff(void){lcdCmd(0x08);}

void lcdScreenOn(void){lcdCmd(0x0C);}

void lcdBlinkCharOn(void){lcdCmd(0x0F);}

void lcdLeftRot(uint8_t cnt){
	uint8_t i;
	for (i=cnt;i>0;i--){
		lcdCmd(0x18);
		delay_ms(400);
	}
}

void lcdRightRot(uint8_t cnt){
	uint8_t i;
	for (i=cnt;i>0;i--){
		lcdCmd(0x1C);
		delay_ms(200);
	}
}

void lcdCursorRight(uint8_t cnt){
	uint8_t i;
	for (i=cnt;i>0;i--){
		lcdCmd(0x14);
	}
}

void lcdCursorLeft(uint8_t cnt){
	uint8_t i;
	for (i=cnt;i>0;i--){
		lcdCmd(0x10);
	}
}

void lcdCursor2Home(){
	lcdCmd(0x02);
}

void lcdBlink(uint8_t cnt){
	uint8_t i;
	for (i=cnt;i>0;i--){
		lcdScreenOff();
		delay_ms(200);
		lcdScreenOn();
		delay_ms(200);
	}
}


void lcdGotoxy( uint8_t x, uint8_t y) {
	/*
	 * x=posicion horizontal desde 1 hasta 16 (Para LCDs de 2X16)
	 * y= posición vertical, 1 o 2(Linea 1 o linea 2)
	 */
	uint8_t i;
	if(y==1){
		i=128;
	}
	else{
		i=192;
	}
   i+=x-1;
   lcdCmd(i);
}

void lcdPuts( char message []) {
	/*
	 * lcdPuts("Mensaje a Imprimir en la LCD");
	 */
	uint8_t i = 0;
	while(message[i] != 0)
	{
		switch (message[i]) {
		case '\f':
			lcdCmd(1);
		    delay_ms(2);
	        break;
	    case '\n':
	    	lcdGotoxy(1,2);
	    	break;
	    case '\b':
	    	lcdCmd(0x10);
	    	delay_ms(2);
	    	break;

	    default:
	    	lcdPutc(message[i]);
	    	break;
		}
		i++;
	}
}



void cursor_back_lcd(uint8_t cnt){
	uint8_t i;
	for (i=cnt;i>0;i--){
		lcdCmd(0x10);
	}
}


void lcdClearL1(void){
	lcdGotoxy(1,1);
	lcdPuts("                        ");
	lcdGotoxy(1,1);
}

void lcdClearL2(void){
	lcdGotoxy(1,2);
	lcdPuts("                        ");
	lcdGotoxy(1,2);
}


void lcdPrintInt16(uint16_t varin){
	char varBuffer[10]="Void";
	printInt16(varBuffer,varin);
	lcdPuts(varBuffer);
}
void lcdPrintInt32(uint32_t varin){
	char varBuffer[10]="Void";
	printInt32(varBuffer,varin);
	lcdPuts(varBuffer);
}
void lcdPrintFloat(float varin,uint8_t FracDigits){
	char varBuffer[15]="Void";
	printFloat(varBuffer,varin,FracDigits);
	lcdPuts(varBuffer);
}

/*void lcdWrite(uint16_t varin){

}
void lcdWrite(float varin){

}*/

#endif

