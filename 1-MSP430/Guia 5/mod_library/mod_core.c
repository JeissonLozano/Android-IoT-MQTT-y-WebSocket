/*
 * mod_core.c
 *
 *  Created on: Mar 5, 2014
 *      Author: wondartinf-01
 */
#include "mod_core.h"



void stopWatchDogTimer(){
	WDTCTL = WDTPW + WDTHOLD;
}

void setDCOFreq(){
	BCSCTL2 = SELM_0 + DIVM_0 + DIVS_0;
	if (CALBC1_xMHZ != 0xFF) {
        	delay_cycles(1000);
			DCOCTL = 0x00;
			BCSCTL1 = CALBC1_xMHZ;      /* Set DCO to 1MHz */
			DCOCTL = CALDCO_xMHZ;
		}
    BCSCTL1 |= XT2OFF | DIVA_0;//Basic Clock System Control 3
    BCSCTL3 = XT2S_0 | LFXT1S_2 | XCAP_1;
}

void delay_ms(uint16_t time_delay){
	while(time_delay--){
		delay_cycles(msec_aj);
	}
}

void delay_us(uint16_t time_delay){

#if DCO_frec_MHz==8
	while(time_delay>8000){
		delay_cycles(64000);//8*8000
		time_delay-=8000;
	}
	time_delay=(time_delay-2)<<3;
#endif
#if DCO_frec_MHz==12
	while(time_delay>5000){
		delay_cycles(60000);//12*5000
		time_delay-=5000;
	}
	time_delay=((time_delay-1)*12)-6;
#endif
#if DCO_frec_MHz==16
	while(time_delay>4000){
		delay_cycles(64000);//16*4000
		time_delay=time_delay-4000;
	}
	time_delay=((time_delay-1)<<4);
#endif

#ifdef __GNUC__

__asm__ (
" sub #20, %[time_delay]\n"
"1: sub #4, %[time_delay] \n"
" nop \n"
" jc 1b \n"
" inv %[time_delay] \n"
" rla %[time_delay] \n"
" add %[time_delay], r0 \n"
" nop \n"
" nop \n"
" nop \n"
: // no output
: [time_delay] "r" (time_delay) // input
: // no memory clobber
);
#else
	time_delay=time_delay >> 3;

	while(time_delay){
		delay_cycles(3);//8 Cycles
		time_delay--;
	}
#endif
}



void delays(uint16_t delayCycles){

#ifdef __GNUC__
	delayCycles+=8;
__asm__ (
" sub #20, %[delayCycles]\n"
"1: sub #4, %[delayCycles] \n"
" nop \n"
" jc 1b \n"
" inv %[delayCycles] \n"
" rla %[delayCycles] \n"
" add %[delayCycles], r0 \n"
" nop \n"
" nop \n"
" nop \n"
: // no output
: [delayCycles] "r" (delayCycles) // input
: // no memory clobber
);
#else
	delayCycles=delayCycles >> 3;

	while(delayCycles){
		delay_cycles(3);//8 Cycles
		delayCycles--;
	}
#endif
}

void  loadBasicSetUp(){
	stopWatchDogTimer();
    setDCOFreq();
#ifdef __MSP430G2553__
    bitLow(P2SEL,BIT7+BIT6);
    bitLow(P2SEL2,BIT7+BIT6);
#endif
}

void actAllInterrupts(){
    __bis_SR_register(GIE);
}
