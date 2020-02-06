/*
 * mod_adc.h
 *
 *  Created on: Mar 11, 2014
 *      Author: wondartinf-01
 */

#ifndef MOD_ADC_H_
#define MOD_ADC_H_
#include "mod_adc10.h"
#include <stdint.h>
#include "mod_core.h"

#define PinChannelA0 BIT0
#define PinChannelA1 BIT1
#define PinChannelA2 BIT2
#define PinChannelA3 BIT3
#define PinChannelA4 BIT4
#define PinChannelA5 BIT5
#define PinChannelA6 BIT6
#define PinChannelA7 BIT7

void adcInit(uint8_t PinsSeleted);
void adcBasicSetUp();
void adcSetUp(uint16_t RegConf0,uint16_t RegConf1);
void adcOn();
void adcOff();
void adcEnaInterrupt();
void adcDisInterrupt();
uint8_t adcFlagInterruptRead();
void adcFlagInterruptClear();

void adcEnaAnalogInput(uint8_t PinsSeleted);
void adcDisAnalogInput(uint8_t PinsSeleted);

void adcStart(uint16_t adcChannel);
uint16_t adcRead(uint16_t adcChannel);
uint16_t adcReadLast();

void adcSelectChannels(uint16_t adcChannel);

void adcUseInternalRef(uint16_t RegRefMask);
void adcUseExternalRef(uint16_t RegRefMask);

float adcGetTempSensorInCelsius();
uint16_t adcGetTempSensor();





#endif /* MOD_ADC_H_ */
