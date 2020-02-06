/*
 * mod_user_defs.h
 *
 *  Created on: Mar 7, 2014
 *      Author: wondartinf-01
 */

#ifndef MOD_USER_DEFS_H_
#define MOD_USER_DEFS_H_

#include "mod_library/mod_pins_io.h"


#define DCO_frec_MHz  16


///////////////////////////////////////
/*Pin IO Definition*/
#define LedGreen  P1_1
#define Button    P1_3
///////////////////////////////////////


///////////////////////////////////////
/*PWM Pins*/
#define pinPWM_01 P1_6
#define pinPWM_02 P2_5

///////////////////////////////////////


///////////////////////////////////////
/*Analog Pins*/
/* Se puede reemplazar la definición
 * (Parte Izquierda) a conveniencia
 * Ej:
 * #define PinSensorPresion PinChannelA0
 * #define SensorPresion ChannelA0
 */

#define pinAna0 PinChannelA0
#define pinAna1 PinChannelA1
#define pinAna2 PinChannelA2
#define pinAna3 PinChannelA3
#define pinAna4 PinChannelA4
#define pinAna5 PinChannelA5
#define pinAna6 PinChannelA6
#define pinAna7 PinChannelA7

#define Ana0 ChannelA0
#define Ana1 ChannelA1
#define Ana2 ChannelA2
#define Ana3 ChannelA3
#define Ana4 ChannelA4
#define Ana5 ChannelA5
#define Ana6 ChannelA6
#define Ana7 ChannelA7
////////////////////////////////////


///////////////////////////////////////
/*LCD*/
#define lcd_rs			P2_3
#define lcd_ena			P2_4
#define lcd_dato4		P2_5
#define lcd_dato5		P1_6
#define lcd_dato6		P2_2
#define lcd_dato7		P1_7
///////////////////////////////////////


///////////////////////////////////////
/*Keypad*/
#define keypad_col1		lcd_dato4//LCD
#define keypad_col2		lcd_dato5//LCD
#define keypad_col3		lcd_dato7//LCD
#define keypad_col4		lcd_dato6//LCD
#define keypad_row1		P2_1//Entradas
#define keypad_row2		P2_0//Entradas
#define keypad_row3		P2_7//Entradas
#define keypad_row4		P1_0//Entradas
///////////////////////////////////////


//////////////////////////////////////
/*UART*/

/*
 * Para Uart Por Software:
 * uart_software_tx/uart_software_rx se escogen los pines a conveniencia
 *uart_swd_frec se escribe El Baudrate a trabajar (Solo Por Software)
 */
#define uart_swd_frec 9600//max=>dco_frec_MHz*1000000/uart_s1_frec-14, el resultado debe ser mayor 10
#define uart_software_tx 	P1_2
#define uart_software_rx 	P1_1

/*
 * Para Uart Por Hardware:
 */
/* 
#ifdef __msp430x22x2
#define uart_tx 	P3_4
#define uart_rx 	P3_5
#else
#endif*/
#define uart_tx 	P1_2
#define uart_rx 	P1_1

//////////////////////////////////////
/*
 * SPI Definiciones de pines
 */
#define spi_simo 	P3_1
#define spi_somi 	P3_2
#define spi_clk 	P3_3
#define spi_cs  	P3_0


#endif /* MOD_USER_DEFS_H_ */
