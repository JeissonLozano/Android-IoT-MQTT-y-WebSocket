/*
 * pins_io.h
 *
 *  Created on: Mar 7, 2014
 *      Author: wondartinf-01
 */

#ifndef PINS_IO_H_
#define PINS_IO_H_

#include "msp430.h"
#include "mod_core.h"


#define bitHigh(x,y) (x)|=(y)
#define bitLow(x,y) (x)&=~(y)
#define bitToggle(x,y) (x)^=(y)

#ifndef __GNUC__

//static uint8_t PVOID_=0x00;
#define PVOID_ 0x00
#ifndef __MSP430G2553
#define P1S2 0x00
#define P2S2 0x00
#define P3S2 0x00
#define P4S2 0x00
#else
#define P1S2 &P1SEL2
#define P2S2 &P2SEL2
#define P3S2 &P3SEL2
#define P4S2 &P4SEL2
#endif
#ifdef __MSP430_HAS_PORT1_R__
//const uint16_t P1Regs[9];
#define P1Regs &P1IN,&P1OUT,&P1DIR,&P1IFG,&P1IES,&P1IE,&P1SEL,P1S2,&P1REN
#define P1_0  P1Regs,BIT0
#define P1_1  P1Regs,BIT1
#define P1_2  P1Regs,BIT2
#define P1_3  P1Regs,BIT3
#define P1_4  P1Regs,BIT4
#define P1_5  P1Regs,BIT5
#define P1_6  P1Regs,BIT6
#define P1_7  P1Regs,BIT7
#endif

#ifdef __MSP430_HAS_PORT2_R__
//const uint16_t P2Regs[9];
#define P2Regs &P2IN,&P2OUT,&P2DIR,&P2IFG,&P2IES,&P2IE,&P2SEL,P2S2,&P2REN
#define P2_0  P2Regs,BIT0
#define P2_1  P2Regs,BIT1
#define P2_2  P2Regs,BIT2
#define P2_3  P2Regs,BIT3
#define P2_4  P2Regs,BIT4
#define P2_5  P2Regs,BIT5
#define P2_6  P2Regs,BIT6
#define P2_7  P2Regs,BIT7
#endif

#ifdef __MSP430_HAS_PORT3_R__
//const uint16_t P3Regs[9];
#define P3Regs &P3IN,&P3OUT,&P3DIR,PVOID_,PVOID_,PVOID_,&P3SEL,P3S2,&P3REN
#define P3_0  P3Regs,BIT0
#define P3_1  P3Regs,BIT1
#define P3_2  P3Regs,BIT2
#define P3_3  P3Regs,BIT3
#define P3_4  P3Regs,BIT4
#define P3_5  P3Regs,BIT5
#define P3_6  P3Regs,BIT6
#define P3_7  P3Regs,BIT7
#endif

#ifdef __MSP430_HAS_PORT4_R__
//const uint16_t P4Regs[9];
#define P4Regs &P4IN,&P4OUT,&P4DIR,PVOID_,PVOID_,PVOID_,&P4SEL,P4S2,&P4REN
#define P4_0  P4Regs,BIT0
#define P4_1  P4Regs,BIT1
#define P4_2  P4Regs,BIT2
#define P4_3  P4Regs,BIT3
#define P4_4  P4Regs,BIT4
#define P4_5  P4Regs,BIT5
#define P4_6  P4Regs,BIT6
#define P4_7  P4Regs,BIT7
#endif

#define arg_fun_inout_0 volatile uint8_t *PxIn,volatile uint8_t *PxOut,volatile uint8_t *PxDir,volatile uint8_t *PxIfg,volatile uint8_t *PxIes,volatile uint8_t *PxIe,volatile uint8_t *PxSel,volatile uint8_t *PxSel2,volatile uint8_t *PxRen,uint8_t pinMask

inline void pinModeOutput(arg_fun_inout_0);
inline void pinModeInput(arg_fun_inout_0);
inline void pinEnaPullUp(arg_fun_inout_0);
inline void pinEnaPullDown(arg_fun_inout_0);
inline void pinDisPullUp(arg_fun_inout_0);
inline void pinDisPullDown(arg_fun_inout_0);
inline void pinEnaIntHighLow(arg_fun_inout_0);
inline void pinEnaIntLowHigh(arg_fun_inout_0);
inline void pinDisInt(arg_fun_inout_0);
inline void pinDisIntHighLow(arg_fun_inout_0);
inline void pinDisIntLowHigh(arg_fun_inout_0);
inline void pinEnaFunc01(arg_fun_inout_0);
inline void pinDigHigh(arg_fun_inout_0);
inline void pinDigLow(arg_fun_inout_0);
inline void pinDigToggle(arg_fun_inout_0);
inline uint8_t pinDigRead(arg_fun_inout_0);
inline uint8_t pinDigReadWith(arg_fun_inout_0,uint8_t pinValue);
inline void pinFlagIntClear(arg_fun_inout_0);
inline uint8_t pinFlagIntRead(arg_fun_inout_0);


inline void pinModeOutput(arg_fun_inout_0){
	bitHigh(*PxDir,pinMask);
}
inline void pinModeInput(arg_fun_inout_0){
	bitLow(*PxDir,pinMask);
}
inline void pinEnaPullUp(arg_fun_inout_0){
	bitHigh(*PxOut,pinMask);
	bitHigh(*PxRen,pinMask);
}
inline void pinEnaPullDown(arg_fun_inout_0){
	bitLow(*PxOut,pinMask);
	bitHigh(*PxRen,pinMask);
}
inline void pinDisPullUp(arg_fun_inout_0){
	bitLow(*PxRen,pinMask);
}
inline void pinDisPullDown(arg_fun_inout_0){
	bitLow(*PxRen,pinMask);
}
inline void pinEnaIntHighLow(arg_fun_inout_0){
	bitHigh(*PxIes,pinMask);
	bitHigh(*PxIe,pinMask);
	bitLow(*PxIfg,pinMask);
}
inline void pinEnaIntLowHigh(arg_fun_inout_0){
	bitLow(*PxIes,pinMask);
	bitHigh(*PxIe,pinMask);
	bitLow(*PxIfg,pinMask);
}
inline void pinDisIntLowHigh(arg_fun_inout_0){
	bitLow(*PxIfg,pinMask);
	bitLow(*PxIe,pinMask);
}
inline void pinDisInt(arg_fun_inout_0){
	bitLow(*PxIfg,pinMask);
	bitLow(*PxIe,pinMask);
}
inline void pinDisIntHighLow(arg_fun_inout_0){
	bitLow(*PxIfg,pinMask);
	bitLow(*PxIe,pinMask);
}
inline void pinEnaFunc01(arg_fun_inout_0){
	bitHigh(*PxSel,pinMask);
#ifdef __MSP430G2553
	bitHigh(*PxSel2,pinMask);
#endif
}
inline void pinDisXtal(arg_fun_inout_0){
	bitLow(*PxSel,pinMask);
}
inline void pinDigHigh(arg_fun_inout_0){
	bitHigh(*PxOut,pinMask);
}
inline void pinDigLow(arg_fun_inout_0){
	bitLow(*PxOut,pinMask);
}
inline void pinDigToggle(arg_fun_inout_0){
	bitToggle(*PxOut,pinMask);
}

inline uint8_t pinDigRead(arg_fun_inout_0){
	return(*PxIn & pinMask);
}
inline uint8_t pinDigReadWith(arg_fun_inout_0,uint8_t pinValue){
	uint8_t Value=10;
	if (*PxIn & pinMask)
		Value=pinValue;
	else
		Value=0;
	return(Value);
}
inline void pinFlagIntClear(arg_fun_inout_0){
	bitLow(*PxIfg,pinMask);
}
inline uint8_t pinFlagIntRead(arg_fun_inout_0){
	return(*PxIfg & pinMask);
}

#else

#ifdef __MSP430_HAS_PORT1_R__
const uint16_t P1Regs[9];
#define P1_0  P1Regs,BIT0
#define P1_1  P1Regs,BIT1
#define P1_2  P1Regs,BIT2
#define P1_3  P1Regs,BIT3
#define P1_4  P1Regs,BIT4
#define P1_5  P1Regs,BIT5
#define P1_6  P1Regs,BIT6
#define P1_7  P1Regs,BIT7
#endif

#ifdef __MSP430_HAS_PORT2_R__
const uint16_t P2Regs[9];
#define P2_0  P2Regs,BIT0
#define P2_1  P2Regs,BIT1
#define P2_2  P2Regs,BIT2
#define P2_3  P2Regs,BIT3
#define P2_4  P2Regs,BIT4
#define P2_5  P2Regs,BIT5
#define P2_6  P2Regs,BIT6
#define P2_7  P2Regs,BIT7
#endif

#ifdef __MSP430_HAS_PORT3_R__
const uint16_t P3Regs[9];
#define P3_0  P3Regs,BIT0
#define P3_1  P3Regs,BIT1
#define P3_2  P3Regs,BIT2
#define P3_3  P3Regs,BIT3
#define P3_4  P3Regs,BIT4
#define P3_5  P3Regs,BIT5
#define P3_6  P3Regs,BIT6
#define P3_7  P3Regs,BIT7
#endif

#ifdef __MSP430_HAS_PORT4_R__
const uint16_t P4Regs[9];
#define P4_0  P4Regs,BIT0
#define P4_1  P4Regs,BIT1
#define P4_2  P4Regs,BIT2
#define P4_3  P4Regs,BIT3
#define P4_4  P4Regs,BIT4
#define P4_5  P4Regs,BIT5
#define P4_6  P4Regs,BIT6
#define P4_7  P4Regs,BIT7
#endif


#define OFFSET_PxDIR  0
#define OFFSET_PxIN   1
#define OFFSET_PxOUT  2
#define OFFSET_PxREN  3
#define OFFSET_PxIES  4
#define OFFSET_PxIE   5
#define OFFSET_PxIFG  6
#define OFFSET_PxSEL  7
#define OFFSET_PxSEL2 8

inline void pinModeOutput(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinModeInput(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinEnaPullUp(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinEnaPullDown(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinDisPullUp(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinDisPullDown(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinEnaIntHighLow(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinEnaIntLowHigh(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinDisIntHighLow(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinDisIntLowHigh(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinEnaFunc01(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinDisXtal(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinDigHigh(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinDigLow(const uint16_t PxRegs[],uint8_t pinMask);
inline void pinDigToggle(const uint16_t PxRegs[],uint8_t pinMask);
inline uint8_t pinDigRead(const uint16_t PxRegs[],uint8_t pinMask);
inline uint8_t pinDigReadWith(const uint16_t PxRegs[],uint8_t pinMask,uint8_t pinValue);
inline void pinFlagIntClear(const uint16_t PxRegs[],uint8_t pinMask);
inline uint8_t pinFlagIntRead(const uint16_t PxRegs[],uint8_t pinMask);

/*
 * Pins Configuration
 */
inline void pinModeOutput(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxDIR]);//Reg PxDIR
	bitHigh(*portDirection,pinMask);
}
inline void pinModeInput(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxDIR]);//Reg PxDIR
	bitLow(*portDirection,pinMask);
}
inline void pinEnaPullUp(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxOUT]);//Reg PxOUT
	bitHigh(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxREN]);//Reg PxREN
	bitHigh(*portDirection,pinMask);
}
inline void pinEnaPullDown(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxOUT]);//Reg PxOUT
	bitLow(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxREN]);//Reg PxREN
	bitHigh(*portDirection,pinMask);
}
inline void pinDisPullUp(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxREN]);//Reg PxREN
	bitLow(*portDirection,pinMask);
}
inline void pinDisPullDown(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxREN]);//Reg PxREN
	bitLow(*portDirection,pinMask);
}
inline void pinEnaIntHighLow(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIES]);//Reg PxIES
	bitHigh(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIFG]);//Reg PxIFG
	bitLow(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIE]);//Reg PxIE
	bitHigh(*portDirection,pinMask);
}
inline void pinEnaIntLowHigh(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIES]);//Reg PxIES
	bitLow(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIFG]);//Reg PxIFG
	bitLow(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIE]);//Reg PxIE
	bitHigh(*portDirection,pinMask);
}
inline void pinDisIntLowHigh(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIFG]);//Reg PxREN
	bitLow(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIE]);//Reg PxREN
	bitLow(*portDirection,pinMask);
}
inline void pinDisIntHighLow(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIFG]);//Reg PxREN
	bitLow(*portDirection,pinMask);
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIE]);//Reg PxREN
	bitLow(*portDirection,pinMask);
}
inline void pinEnaFunc01(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxSEL]);//Reg PxOUT
	bitHigh(*portDirection,pinMask);
#if defined(P1SEL2)|(P1SEL2_)
	portDirection = (uint8_t)(PxRegs[OFFSET_PxSEL2]);//Reg PxSEL2
	bitHigh(*portDirection,pinMask);
#endif
}

inline void pinDisXtal(const uint16_t PxRegs[],uint8_t pinMask){
	uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxSEL]);//Reg PxOUT
	bitLow(*portDirection,pinMask);
}


/*
 * Pins Digital Output/Input Access
 */
inline void pinDigHigh(const uint16_t PxRegs[],uint8_t pinMask){
	volatile uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxOUT]);//Reg PxOUT
	bitHigh(*portDirection,pinMask);
}
inline void pinDigLow(const uint16_t PxRegs[],uint8_t pinMask){
	volatile uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxOUT]);//Reg PxOUT
	bitLow(*portDirection,pinMask);
}
inline void pinDigToggle(const uint16_t PxRegs[],uint8_t pinMask){
	volatile uint8_t *portDirection;
	portDirection=(uint8_t)(PxRegs[OFFSET_PxOUT]);//Reg PxOUT
	bitToggle(*portDirection,pinMask);
}

inline uint8_t pinDigRead(const uint16_t PxRegs[],uint8_t pinMask){
	volatile uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIN]);//Reg PxIN
	return((uint8_t)(*portDirection & (pinMask)));
}
inline uint8_t pinDigReadWith(const uint16_t PxRegs[],uint8_t pinMask,uint8_t pinValue){
	uint8_t value=10;
	volatile uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIN]);
	if(*portDirection & (pinMask))
		value=pinValue;
	else
		value=0;
	return(value);
}

inline void pinFlagIntClear(const uint16_t PxRegs[],uint8_t pinMask){
	volatile uint8_t *portDirection;
	portDirection=(uint8_t)(PxRegs[OFFSET_PxIFG]);//Reg PxOUT
	bitLow(*portDirection,pinMask);
}
inline uint8_t pinFlagIntRead(const uint16_t PxRegs[],uint8_t pinMask){
	volatile uint8_t *portDirection;
	portDirection = (uint8_t)(PxRegs[OFFSET_PxIFG]);//Reg PxIN
	return((uint8_t)(*portDirection & (pinMask)));
}
#endif





#endif /* PINS_IO_H_ */
