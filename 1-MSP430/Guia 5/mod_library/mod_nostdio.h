/*
 * mod_nostdio.h
 *
 *  Created on: Mar 7, 2014
 *      Author: fabianrcm
 */

#ifndef MOD_NOSTDIO_H_
#define MOD_NOSTDIO_H_

#include "msp430.h"
#include <stdint.h>


inline char intToChar(char var_int);

uint8_t putString(char *var,uint8_t start_pos,char message []);
uint8_t putFloat(char *var,uint8_t start_pos,float var_float,uint8_t dig_bdot,uint8_t dig_adot);
uint8_t putInt8(char *var,uint8_t start_pos,uint8_t var_int,uint8_t dig_bdot);
uint8_t putInt16(char *var,uint8_t start_pos,uint16_t var_int,uint8_t dig_bdot);
//void (*printFloat)(char *var,uint8_t FractDigit);
uint8_t printFloat(char *var,float var_float,uint8_t FractDigit);
uint8_t printInt16(char *var,uint16_t var_int);
uint8_t printInt32(char *var,uint32_t var_int);
inline char intToChar(char var_int){return(var_int+48);}


uint8_t putStringBuffer(char *pBuffer,uint8_t pBufferPos,char var[]);
uint8_t putcBuffer(char *pBuffer,uint8_t pBufferPos,char varIn);
uint8_t putInt16Buffer(char *pBuffer,uint8_t pBufferPos, uint16_t var);
uint8_t putInt32Buffer(char *pBuffer,uint8_t pBufferPos, uint32_t var);
uint8_t putFloatBuffer(char *pBuffer,uint8_t pBufferPos,float var,uint8_t var1);


#endif /* MOD_NOSTDIO_H_ */
