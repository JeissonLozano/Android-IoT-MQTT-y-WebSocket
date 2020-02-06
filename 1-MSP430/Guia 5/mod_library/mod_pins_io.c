/*
 * pins_io.c
 *
 *  Created on: Mar 7, 2014
 *      Author: wondartinf-01
 */

#include "mod_pins_io.h"

#ifdef __GNUC__

/*
 * PORT 1 Associated Registers
 */
#ifdef __MSP430_HAS_PORT1_R__
const uint16_t P1Regs[9]={
		(uint16_t)&P1DIR,//0
		(uint16_t)&P1IN,//1
		(uint16_t)&P1OUT,//2
		(uint16_t)&P1REN,//3
		(uint16_t)&P1IES,//4
		(uint16_t)&P1IE,//5
		(uint16_t)&P1IFG,//6
#if defined(P1SEL)|(P1SEL_)
		(uint16_t)&P1SEL,//7
#else
		0,
#endif
#if defined(P1SEL2)|(P1SEL2_)
		(uint16_t)&P1SEL2//8
#else
		0,
#endif
};
#endif

/*
 * PORT 2 Associated Registers
 */
#ifdef __MSP430_HAS_PORT2_R__
const uint16_t P2Regs[9]={
		(uint16_t)&P2DIR,//0
		(uint16_t)&P2IN,//1
		(uint16_t)&P2OUT,//2
		(uint16_t)&P2REN,//3
		(uint16_t)&P2IES,//4
		(uint16_t)&P2IE,//5
		(uint16_t)&P2IFG,//6
#if defined(P2SEL)|(P2SEL_)
		(uint16_t)&P2SEL,//7
#else
		0,
#endif
#if defined(P2SEL2)|(P2SEL2_)
		(uint16_t)&P2SEL2//8
#else
		0,
#endif
};
#endif


/*
 * PORT 3 Associated Registers
 */
#ifdef __MSP430_HAS_PORT3_R__
const uint16_t P3Regs[9]={
		(uint16_t)&P3DIR,//0
		(uint16_t)&P3IN,//1
		(uint16_t)&P3OUT,//2
		(uint16_t)&P3REN,//3
		0,//4
		0,//5
		0,//6
#if defined(P3SEL)|(P3SEL_)
		(uint16_t)&P3SEL,//7
#else
		0,
#endif
#if defined(P3SEL2)|(P3SEL2_)
		(uint16_t)&P1SEL2//8
#else
		0,
#endif
};
#endif

/*
 * PORT 4 Associated Registers
 */
#ifdef __MSP430_HAS_PORT4_R__
const uint16_t P4Regs[9]={
		(uint16_t)&P4DIR,//0
		(uint16_t)&P4IN,//1
		(uint16_t)&P4OUT,//2
		(uint16_t)&P4REN,//3
		0,//4
		0,//5
		0,//6
#if defined(P4SEL)|(P4SEL_)
		(uint16_t)&P4SEL,//7
#else
		0,
#endif
#if defined(P4SEL2)|(P4SEL2_)
		(uint16_t)&P4SEL2//8
#else
		0,
#endif
};
#endif

#endif
