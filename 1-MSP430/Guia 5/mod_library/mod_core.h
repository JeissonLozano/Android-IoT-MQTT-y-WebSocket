/*
 * mod_core.h
 *
 *  Created on: Mar 5, 2014
 *      Author: wondartinf-01
 */

#ifndef MOD_CORE_H_
#define MOD_CORE_H_

#include "msp430.h"
#include <stdint.h>
#include "../mod_user_defs.h"

#define delay_cycles  __delay_cycles
#define DCO_frec_KHz  DCO_frec_MHz*1000

#define usec    DCO_frec_MHz
#define msec    DCO_frec_MHz*1000
#define msec_aj	 msec-5


#define bitHigh(x,y) (x)|=(y)
#define bitLow(x,y) (x)&=~(y)
#define bitToggle(x,y) (x)^=(y)

void stopWatchDogTimer();
void setDCOFreq();
void delay_ms(uint16_t time_delay);


void delay_us(uint16_t time_delay);




void delays(uint16_t delayCycles);

void  loadBasicSetUp();
void actAllInterrupts();



#if DCO_frec_MHz==1
#define CALBC1_xMHZ CALBC1_1MHZ
#define CALDCO_xMHZ CALDCO_1MHZ
#endif
#if DCO_frec_MHz==8
#define CALBC1_xMHZ CALBC1_8MHZ
#define CALDCO_xMHZ CALDCO_8MHZ
#endif
#if DCO_frec_MHz==12
#define CALBC1_xMHZ CALBC1_12MHZ
#define CALDCO_xMHZ CALDCO_12MHZ
#endif
#if DCO_frec_MHz==16
#define CALBC1_xMHZ CALBC1_16MHZ
#define CALDCO_xMHZ CALDCO_16MHZ
#endif


#endif /* MOD_CORE_H_ */
