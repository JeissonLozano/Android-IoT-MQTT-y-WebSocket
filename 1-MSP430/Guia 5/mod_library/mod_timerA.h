/*
 * mod_timerA.h
 *
 *  Created on: Apr 2, 2014
 *      Author: wondartinf-01
 */

#ifndef MOD_TIMERA_H_
#define MOD_TIMERA_H_
#include "../mod_user_defs.h"

//TACTL, Timer_A Control Register
#define TimerACLKSource_pinCLK (TASSEL_0)
#define TimerACLKSource_ACLK   (TASSEL_1)
#define TimerACLKSource_SMCLK  (TASSEL_2)
#define TimerACLKSource_INCLK  (TASSEL_3)
#define TimerACLKDivBy_1       (ID_0)
#define TimerACLKDivBy_2       (ID_1)
#define TimerACLKDivBy_4       (ID_2)
#define TimerACLKDivBy_8       (ID_3)
#define TimerAStopMode         (MC_0)
#define TimerAUpMode           (MC_1)
#define TimerAContinuousMode   (MC_2)
#define TimerAUpDownMode       (MC_3)
#define TimerAReset            (TACLR)
#define TimerAInterruptOn      (TAIE)
#define TimerAIntFlagIsPending (TAIFG)

//TACCTLx, Capture/Compare Control Register
#define CaptMode_RisingEdge    (CM_1)
#define CaptMode_FallingEdge   (CM_2)
#define CaptMode_BothEdges     (CM_3)
#define CaptCompInputCCIxA     (CCIS_0)
#define CaptCompInputCCIxB     (CCIS_1)
#define CaptCompInputGND       (CCIS_2)
#define CaptCompInputVCC       (CCIS_3)
#define SyncCapt               (SCS)
#define AsyncCapt              (0x00)
#define CaptureMode            (CAP)
#define CompareMode            (0x00)
#define OutputMode_Set         (OUTMOD_1)
#define OutputMode_ToggleReset (OUTMOD_2)
#define OutputMode_SetReset    (OUTMOD_3)
#define OutputMode_Toggle      (OUTMOD_4)
#define OutputMode_Reset       (OUTMOD_5)
#define OutputMode_ToggleSet   (OUTMOD_6)
#define OutputMode_ResetSet    (OUTMOD_7)
#define CaptComp_InterruptOn   (CCIE)
#define CaptComp_InterruptOff  (0x00)
#define CaptOverFlowOn         (CAOV)
#define CaptOverFlowOff        (0x00)
#define CaptComp_IntFlag       (CCIFG)


#define TIMER_A0               (TA0CTL)
#define TIMER_A0_VALUE         (TA0R)
#define TIMER_A0_CC0           (TA0CCTL0)
#define TIMER_A0_CC0_VALUE     (TA0CCR0)
#define TIMER_A0_CC1           (TA0CCTL1)
#define TIMER_A0_CC1_VALUE     (TA0CCR1)
#define TIMER_A0_CC2           (TA0CCTL2)
#define TIMER_A0_CC2_VALUE     (TA0CCR2)


#ifndef __GNUC__
void pinEnaFunTimer(arg_fun_inout_0);
void pinEnaPWM(arg_fun_inout_0);
#else
void pinEnaFunTimer(const uint16_t PxRegs[],uint8_t pinMask);
void pinEnaPWM(const uint16_t PxRegs[],uint8_t pinMask);
#endif

#define timerSetup(x,y) (x)=(y)

#if defined(__MSP430_HAS_TA3__)

inline void timerA0InitCounter(uint16_t bitMask);
inline void timerA0InitCounter(uint16_t bitMask){	TA0CTL = bitMask + TimerAContinuousMode;}

inline void timerA0ClearCounter(void);
inline void timerA0ClearCounter(void){bitHigh(TA0CTL,TimerAReset);}

inline void timerA0StopCounter(void);
inline void timerA0StopCounter(void){bitLow(TA0CTL,TimerAContinuousMode);}

inline void timerA0StartCounter(void);
inline void timerA0StartCounter(void){bitHigh(TA0CTL,TimerAContinuousMode);}

inline void timerA0ClearOverFlow(void);
inline void timerA0ClearOverFlow(void){bitLow(TA0CTL,TAIFG);}

inline uint8_t timerA0CheckOverFlow(void);
inline uint8_t timerA0CheckOverFlow(void){return(TA0CTL & TAIFG);}

inline uint16_t timerA0GetCounterValue(void);
inline uint16_t timerA0GetCounterValue(void){return(TA0R);}

void timerA0InitInterrupts(uint8_t clkPreescaler,uint16_t clkCounter);
void timerA0InitPWM1(uint8_t clkPreescaler,uint16_t freqCounter,uint16_t dutyCounter);
void timerA0InitPWM2(uint8_t clkPreescaler,uint16_t freqCounter,uint16_t dutyCounter);
void timerA0DutyCyclePWM1(uint16_t dutyCounter);
void timerA0DutyCyclePWM2(uint16_t dutyCounter);
#endif

#if defined(__MSP430_HAS_T1A3__)

inline void timerA1InitCounter(uint16_t bitMask);
inline void timerA1InitCounter(uint16_t bitMask){	TA1CTL = bitMask + TimerAContinuousMode;}

inline void timerA1ClearCounter(void);
inline void timerA1ClearCounter(void){bitHigh(TA1CTL,TimerAReset);}

inline void timerA1StopCounter(void);
inline void timerA1StopCounter(void){bitLow(TA1CTL,TimerAContinuousMode);}

inline void timerA1StartCounter(void);
inline void timerA1StartCounter(void){bitHigh(TA1CTL,TimerAContinuousMode);}

inline void timerA1ClearOverFlow(void);
inline void timerA1ClearOverFlow(void){bitLow(TA1CTL,TAIFG);}

inline uint8_t timerA1CheckOverFlow(void);
inline uint8_t timerA1CheckOverFlow(void){return(TA1CTL & TAIFG);}

inline uint16_t timerA1GetCounterValue(void);
inline uint16_t timerA1GetCounterValue(void){return(TA1R);}

void timerA1InitInterrupts(uint8_t clkPreescaler,uint16_t clkCounter);
void timerA1InitPWM1(uint8_t clkPreescaler,uint16_t freqCounter,uint16_t dutyCounter);
void timerA1InitPWM2(uint8_t clkPreescaler,uint16_t freqCounter,uint16_t dutyCounter);
void timerA1DutyCyclePWM1(uint16_t dutyCounter);
void timerA1DutyCyclePWM2(uint16_t dutyCounter);
#endif


#endif /* MOD_TIMERA_H_ */
