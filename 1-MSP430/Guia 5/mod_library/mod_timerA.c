/*
 * mod_timerA.c
 *
 *  Created on: Apr 2, 2014
 *      Author: wondartinf-01
 */
#include "mod_timerA.h"


#if defined(__MSP430_HAS_TA3__)
#ifndef __GNUC__

void pinEnaFunTimer(volatile uint8_t *PxIn,volatile uint8_t *PxOut,volatile uint8_t *PxDir,volatile uint8_t *PxIfg,volatile uint8_t *PxIes,volatile uint8_t *PxIe,volatile uint8_t *PxSel,volatile uint8_t *PxSel2,volatile uint8_t *PxRen,uint8_t pinMask){
	bitHigh(*PxSel,pinMask);
	bitLow(*PxSel,pinMask);
}
void pinEnaPWM(volatile uint8_t *PxIn,volatile uint8_t *PxOut,volatile uint8_t *PxDir,volatile uint8_t *PxIfg,volatile uint8_t *PxIes,volatile uint8_t *PxIe,volatile uint8_t *PxSel,volatile uint8_t *PxSel2,volatile uint8_t *PxRen,uint8_t pinMask){
	bitHigh(*PxDir,pinMask);
	bitHigh(*PxSel,pinMask);
	bitLow(*PxSel2,pinMask);
}

#else
void pinEnaFunTimer(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxSEL]);//Reg PxDIR
	bitHigh(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxSEL2]);//Reg PxDIR
	bitLow(*portDirection,pinMask);
}
void pinEnaPWM(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxDIR]);//Reg PxDIR
	bitHigh(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxSEL]);//Reg PxDIR
	bitHigh(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxSEL2]);//Reg PxDIR
	bitLow(*portDirection,pinMask);
}
#endif


void timerA0InitInterrupts(uint8_t clkPreescaler,uint16_t clkCounter){
	/*
	 * Freq Interrupt = Freq CPU / (clkPreescaler * clkCounter)
	 * Configura el módulo del timer para obtener interrupciones
	 * a determinada frecuencia
	 *
	 */
	timerSetup(TIMER_A0,TimerACLKSource_SMCLK + clkPreescaler + TimerAUpMode);
	timerSetup(TIMER_A0_CC0,CaptComp_InterruptOn);
	timerSetup(TIMER_A0_CC0_VALUE,clkCounter);
}
void timerA0InitPWM1(uint8_t clkPreescaler,uint16_t freqCounter,uint16_t dutyCounter){
	/*
	 * dutyCounter<=freqCounter
	 * Configura la frecuencia y el ciclo util de TimerA0 CC1
	 * Freq PWM = Freq CPU / (clkPreescaler * freqCounter)
	 * Configura el módulo del timer para obtener PWM con frecuencia
	 * manejada por el modulo de captura-compracion 0
	 * y ciclo útil por el modulo de captura-comparacion 1
	 *
	 * clkPreescaler:
	 *TimerACLKDivBy_1
	 *TimerACLKDivBy_2
	 *TimerACLKDivBy_4
	 *TimerACLKDivBy_8
	 *
	 * Ejemplo:
	 * timerA0InitPWM1(TimerACLKDivBy_2,1000,500);
	 * si trabaja con la cpu a 1MHZ:
	 * 1000/1000000Hz=1000uS=1mS
	 * 500/1000000Hz=500uS=0.5mS
	 * Entonces se tiene el PWM oscilando a 1Khz con un duty del 50%
	 *
	 */
	timerSetup(TIMER_A0_CC0_VALUE,freqCounter);
	timerSetup(TIMER_A0_CC1_VALUE,dutyCounter);
	timerSetup(TIMER_A0_CC1,OutputMode_ResetSet);
	timerSetup(TIMER_A0,TimerACLKSource_SMCLK + clkPreescaler + TimerAUpMode);
}
void timerA0InitPWM2(uint8_t clkPreescaler,uint16_t freqCounter,uint16_t dutyCounter){
	/*
	 * dutyCounter<=freqCounter
	 * Configura la frecuencia y el ciclo util de TimerA0 CC2
	 * Freq PWM = Freq CPU / (clkPreescaler * freqCounter)
	 * Configura el módulo del timer para obtener PWM con frecuencia
	 * manejada por el modulo de captura-compracion 0
	 * y ciclo útil por el modulo de captura-comparacion 1
	 *
	 * clkPreescaler:
	 *TimerACLKDivBy_1
	 *TimerACLKDivBy_2
	 *TimerACLKDivBy_4
	 *TimerACLKDivBy_8
	 *
	 *	 * Ejemplo:
	 * timerA0InitPWM2(TimerACLKDivBy_2,1000,500);
	 * si trabaja con la cpu a 1MHZ:
	 * 1000/1000000Hz=1000uS=1mS
	 * 500/1000000Hz=500uS=0.5mS
	 * Entonces se tiene el PWM oscilando a 1Khz con un duty del 50%
	 *
	 */
	timerSetup(TIMER_A0_CC0_VALUE,freqCounter);
	timerSetup(TIMER_A0_CC2_VALUE,dutyCounter);
	timerSetup(TIMER_A0_CC2,OutputMode_ResetSet);
	timerSetup(TIMER_A0,TimerACLKSource_SMCLK + clkPreescaler + TimerAUpMode);
}
void timerA0DutyCyclePWM1(uint16_t dutyCounter){
	TIMER_A0_CC1_VALUE = dutyCounter ;
}
void timerA0DutyCyclePWM2(uint16_t dutyCounter){
	TIMER_A0_CC2_VALUE = dutyCounter;
}

#endif



#if defined(__MSP430_HAS_T1A3__)
void timerA1InitInterrupts(uint8_t clkPreescaler,uint16_t clkCounter){
	/*
	 * dutyCounter<=freqCounter
	 * Freq Interrupt = Freq CPU / (clkPreescaler * clkCounter)
	 * Configura el módulo del timer para obtener interrupciones
	 * a determinada frecuencia
	 *
	 */
	TA1CTL = TimerACLKSource_SMCLK + clkPreescaler + TimerAUpMode;
	TA1CCTL0 = CaptComp_InterruptOn;
	TA1CCR0 = clkCounter;
}
void timerA1InitPWM1(uint8_t clkPreescaler,uint16_t freqCounter,uint16_t dutyCounter){
	/*
	 * dutyCounter<=freqCounter
	 * Freq PWM = Freq CPU / (clkPreescaler * freqCounter)
	 * Configura el módulo del timer para obtener PWM con frecuencia
	 * manejada por el modulo de captura-compracion 0
	 * y ciclo útil por el modulo de captura-comparacion 1
	 * clkPreescaler:
	 *TimerACLKDivBy_1
	 *TimerACLKDivBy_2
	 *TimerACLKDivBy_4
	 *TimerACLKDivBy_8
	 *
	 *	 * Ejemplo:
	 * timerA1InitPWM1(TimerACLKDivBy_2,1000,500);
	 * si trabaja con la cpu a 1MHZ:
	 * 1000/1000000Hz=1000uS=1mS
	 * 500/1000000Hz=500uS=0.5mS
	 * Entonces se tiene el PWM oscilando a 1Khz con un duty del 50%
	 *
	 */
	TA1CCR0 = freqCounter;
	TA1CCR1 = dutyCounter;
	TA1CCR2 = dutyCounter;
	TA1CCTL1 = OutputMode_ResetSet;
	TA1CCTL2 = OutputMode_ResetSet;

	TA1CTL = TimerACLKSource_SMCLK + clkPreescaler + TimerAUpMode;
}
void timerA1InitPWM2(uint8_t clkPreescaler,uint16_t freqCounter,uint16_t dutyCounter){
	/*
	 * dutyCounter<=freqCounter
	 *
	 * Freq PWM = Freq CPU / (clkPreescaler * freqCounter)
	 * Configura el módulo del timer para obtener PWM con frecuencia
	 * manejada por el modulo de captura-compracion 0
	 * y ciclo útil por el modulo de captura-comparacion 1
	 * clkPreescaler:
	 *TimerACLKDivBy_1
	 *TimerACLKDivBy_2
	 *TimerACLKDivBy_4
	 *TimerACLKDivBy_8
	 * Ejemplo:
	 * timerA1InitPWM2(TimerACLKDivBy_2,1000,500);
	 * si trabaja con la cpu a 1MHZ:
	 * 1000/1000000Hz=1000uS=1mS
	 * 500/1000000Hz=500uS=0.5mS
	 * Entonces se tiene el PWM oscilando a 1Khz con un duty del 50%
	 */
	TA1CCR0 = freqCounter;
	TA1CCR2 = dutyCounter;
	TA1CCTL2 = OutputMode_ResetSet;
	TA1CTL = TimerACLKSource_SMCLK + clkPreescaler + TimerAUpMode;
}
void timerA1DutyCyclePWM1(uint16_t dutyCounter){
	TA1CCR1 = dutyCounter ;
}
void timerA1DutyCyclePWM2(uint16_t dutyCounter){
	TA1CCR2 = dutyCounter;
}
#endif


