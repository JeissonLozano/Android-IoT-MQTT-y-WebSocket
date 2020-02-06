/*
 * mod_tecmatrix.c
 *
 *  Created on: Mar 15, 2014
 *      Author: fabianrcm
 */

#include "mod_keypad.h"

const char TecArray[16]={
		'1','2','3','A',
		'4','5','6','B',
		'7','8','9','C',
		'*','0','#','D',
};

#if defined(keypad_col1) & defined(keypad_col2) & defined(keypad_col3) & defined(keypad_col4) & defined(keypad_row1) & defined(keypad_row2) & defined(keypad_row3) & defined(keypad_row4)

void keypadInit(){
	pinModeOutput(keypad_col1);pinModeOutput(keypad_col2);pinModeOutput(keypad_col3);pinModeOutput(keypad_col4);
	keypadDisable();
	pinModeInput(keypad_row1);pinModeInput(keypad_row2);pinModeInput(keypad_row3);pinModeInput(keypad_row4);
	pinEnaPullUp(keypad_row1);pinEnaPullUp(keypad_row2);pinEnaPullUp(keypad_row3);pinEnaPullUp(keypad_row4);
}
void keypadEnable(){
	pinDigHigh(keypad_col1);pinDigHigh(keypad_col2);pinDigHigh(keypad_col3);pinDigHigh(keypad_col4);
}
void keypadDisable(){
	pinDigLow(keypad_col1);pinDigLow(keypad_col2);pinDigLow(keypad_col3);pinDigLow(keypad_col4);
}
uint8_t keypadStatus(){
	uint8_t status=10;
	keypadDisable();
	if(pinDigReadWith(keypad_row1,1) & pinDigReadWith(keypad_row2,1) & pinDigReadWith(keypad_row3,1) & pinDigReadWith(keypad_row4,1))
		status=NOPRESS;
	else
		status=PRESS;
	return (status);
}


uint8_t keypadGetc(){
	char var=0;
	keypadEnable();pinDigLow(keypad_col1);
	if(pinDigRead(keypad_row1)==0)
		var=TecArray[0];
	if(pinDigRead(keypad_row2)==0)
		var=TecArray[1];
	if(pinDigRead(keypad_row3)==0)
		var=TecArray[2];
	if(pinDigRead(keypad_row4)==0)
		var=TecArray[3];

	keypadEnable();pinDigLow(keypad_col2);
	if(pinDigRead(keypad_row1)==0)
		var=TecArray[4];
	if(pinDigRead(keypad_row2)==0)
		var=TecArray[5];
	if(pinDigRead(keypad_row3)==0)
		var=TecArray[6];
	if(pinDigRead(keypad_row4)==0)
		var=TecArray[7];

	keypadEnable();pinDigLow(keypad_col3);
	if(pinDigRead(keypad_row1)==0)
		var=TecArray[8];
	if(pinDigRead(keypad_row2)==0)
		var=TecArray[9];
	if(pinDigRead(keypad_row3)==0)
		var=TecArray[10];
	if(pinDigRead(keypad_row4)==0)
		var=TecArray[11];

	keypadEnable();pinDigLow(keypad_col4);
	if(pinDigRead(keypad_row1)==0)
		var=TecArray[12];
	if(pinDigRead(keypad_row2)==0)
		var=TecArray[13];
	if(pinDigRead(keypad_row3)==0)
		var=TecArray[14];
	if(pinDigRead(keypad_row4)==0)
		var=TecArray[15];
	keypadDisable();
	return(var);
}

uint8_t keypadGetChar(uint16_t timeOut,uint8_t SendCharTo,char MaskChar){
	char CharGet=0;
	while((keypadStatus() == NOPRESS) && (timeOut>0)){
		delay_ms(1);
		timeOut--;
	}
	if(timeOut==0){
		return(0);
	}
	CharGet=keypadGetc();
	if(SendCharTo==PrintToLCD){
		if(MaskChar==NoMaskToChar){
			lcdPutc(CharGet);
		}else{
			lcdPutc(MaskChar);
		}
	}
	delay_ms(timeOut);
	return (CharGet);
}

uint8_t keypadWaitChar(uint16_t timeOut,uint8_t SendCharTo,char MaskChar){
	char CharGet=0;
	while((keypadStatus() == NOPRESS)){	}
	CharGet=keypadGetc();
	if(SendCharTo==PrintToLCD){
		if(MaskChar==NoMaskToChar){
			lcdPutc(CharGet);
		}else{
			lcdPutc(MaskChar);
		}
	}
	delay_ms(timeOut);
	return (CharGet);
}

uint8_t keypadWaitString(char *VarBuffer,uint8_t PosMem,uint8_t NumOfChars,uint16_t timeOut,uint8_t SendCharTo,char MaskChar){
	/*Catch a characters sequence and save it in VarBuffer
	 * It return the last Free position of VarBuffer
	 */
	char CharGet=0;
	while(NumOfChars){
		CharGet=keypadWaitChar(timeOut,SendCharTo,MaskChar);
		VarBuffer[PosMem]=CharGet;
		NumOfChars--;PosMem++;
	}
	VarBuffer[PosMem]=0;
	return(PosMem);
}
uint8_t keypadGetsUntil(char *VarBuffer,uint8_t PosMem,char CharStop,uint16_t timeOut,uint8_t SendCharTo,char MaskChar){
	/*Catch a characters sequence and save it in VarBuffer
	 * It return the last Free position of VarBuffer
	 */
	char CharGet=0;
	do{
		CharGet = keypadWaitChar(timeOut,NoPrint,NoMaskToChar);
		if(CharGet==CharStop){
			VarBuffer[PosMem]=0;
		}else{
			if(SendCharTo==PrintToLCD){
				if(MaskChar==NoMaskToChar){
					lcdPutc(CharGet);
				}else{
					lcdPutc(MaskChar);
				}
			}
			VarBuffer[PosMem]=CharGet;
			PosMem++;
		}
	}while(CharGet != CharStop);
	return(PosMem);
}


void keypadLineInit(void){
    pinModeInput(keypad_row1);
    pinEnaPullUp(keypad_row1);
}
char keypadLineGetc(){
	char var=0;
	keypadEnable();pinDigLow(keypad_col1);
	if(pinDigRead(keypad_row1)==0){
	    var = 'D';
	}
	keypadEnable();pinDigLow(keypad_col2);
	if(pinDigRead(keypad_row1)==0){
	    var = 'R';
	}
	keypadEnable();pinDigLow(keypad_col3);
	if(pinDigRead(keypad_row1)==0){
	    var = 'U';
	}
	keypadEnable();pinDigLow(keypad_col4);
	if(pinDigRead(keypad_row1)==0){
	    var = 'L';
	}
	keypadDisable();
	return var;
}



#endif
