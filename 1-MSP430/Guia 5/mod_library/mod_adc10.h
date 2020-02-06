/*
 * mod_adc10.h
 *
 *  Created on: Mar 9, 2014
 *      Author: fabianrcm
 */

#ifndef MOD_ADC10_H_
#define MOD_ADC10_H_

#include "msp430.h"

/*
 * ADC10CTL0, ADC10 Control Register 0
 */
//Vrs Voltaje de referencia superior
//Vers Voltaje externo de referencia superior

#define VRefSupVcc_VRefInfVss    	    (SREF_0)
#define VRefSupInternal_VRefInfVss     (SREF_1)
#define VRefSupExternal_VRefInfVss     (SREF_2)
#define VRefSupBufExt_VRefInfVss    	(SREF_3)
#define VRefSupVcc_VRefInfExt          (SREF_4)
#define VRefSupInternal_VRefInfExt     (SREF_5)
#define VRefSupExternal_VRefInfExt     (SREF_6)
#define VRefSupBufExt_VRefInfExt       (SREF_7)
#define SHTime_4CLKs                   (ADC10SHT_0)
#define SHTime_8CLKs                   (ADC10SHT_1)
#define SHTime_16CLKs                  (ADC10SHT_2)
#define SHTime_64CLKs                  (ADC10SHT_3)
#define SamplingRate_50Ksps            (ADC10SR)
#define SamplingRate_200Ksps           (0x00)
#define RefOutput_On                   (REFOUT)
#define RefOutput_Off                  (0x00)
#define RefBufCont_On                  (REFBURST)
#define RefBufCont_Off                 (0x00)
#define RefInternalIs2_5V              (REF2_5V)
#define RefInternalIs1_5V              (0x00)
#define RefInternal_On                 (REFON)
#define RefInternal_Off                (0x00)
#define ADC10_On                       (ADC10ON)
#define ADC10_Off                      (0x00)
#define ADC10Int_On                    (ADC10IE)
#define ADC10Int_Off                   (0x00)
#define ADC10IntFlagIsPending          (ADC10IFG)
#define ADC10IntFlagNoIsPending        (0x00)
#define ADC10Conv_On                   (ENC)
#define ADC10Conv_Off                  (0x00)
#define ADC10StartSamAndConv           (ADC10SC)
#define ADC10StopSamAndConv            (0x00)


/*
 * ADC10CTL1, ADC10 Control Register 1
 */
#define ChannelA0              (INCH_0)
#define ChannelA1              (INCH_1)
#define ChannelA2              (INCH_2)
#define ChannelA3              (INCH_3)
#define ChannelA4              (INCH_4)
#define ChannelA5              (INCH_5)
#define ChannelA6              (INCH_6)
#define ChannelA7              (INCH_7)
#define ChannelExternalRefSup  (INCH_8)
#define ChannelExternalRefInf  (INCH_9)
#define ChannelTempSensor      (INCH_10)
#define ChannelSupply_2        (INCH_11)
#define ChannelA12             (INCH_12)
#define ChannelA13             (INCH_13)
#define ChannelA14             (INCH_14)
#define ChannelA15             (INCH_15)
#define MSbBit15               (ADC10DF)
#define MSbBit9                (0x00)
#define ADC10CLKDivBy_1        (ADC10DIV_0)
#define ADC10CLKDivBy_2        (ADC10DIV_1)
#define ADC10CLKDivBy_3        (ADC10DIV_2)
#define ADC10CLKDivBy_4        (ADC10DIV_3)
#define ADC10CLKDivBy_5        (ADC10DIV_4)
#define ADC10CLKDivBy_6        (ADC10DIV_5)
#define ADC10CLKDivBy_7        (ADC10DIV_6)
#define ADC10CLKDivBy_8        (ADC10DIV_7)
#define ADC10CLKSorce_ADCOsc   (ADC10SSEL_0)
#define ADC10CLKSorce_ACLK     (ADC10SSEL_1)
#define ADC10CLKSorce_MCLK     (ADC10SSEL_2)
#define ADC10CLKSorce_SMCLK    (ADC10SSEL_3)
#define SingleChannelSingleConversion (CONSEQ_0)
#define SequenceOfChannels            (CONSEQ_1)
#define RepeatSingleChannel           (CONSEQ_2)
#define RepeatSequenceOfChannels      (CONSEQ_3)
#define ADC10IsBusy                   (ADC10BUSY)








#endif /* MOD_ADC10_H_ */
