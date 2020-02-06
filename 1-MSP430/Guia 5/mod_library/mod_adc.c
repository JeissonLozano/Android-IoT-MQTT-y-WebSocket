/*
 * mod_adc.c
 *
 *  Created on: Mar 9, 2014
 *      Author: fabianrcm
 */
#include "mod_adc.h"

void adcInit(uint8_t PinsSeleted){
	adcBasicSetUp();
	adcEnaAnalogInput(PinsSeleted);
}

void adcBasicSetUp(){
	/*
	 * Voltaje of Reference is Vcc
	 * Single Conversion and single channel
	 */
	bitLow(ADC10CTL0,ENC);
	ADC10CTL1 = SingleChannelSingleConversion + ADC10CLKSorce_ADCOsc + ADC10CLKDivBy_1;
	ADC10CTL0 = ADC10ON + SHTime_16CLKs + VRefSupVcc_VRefInfVss;
}
void adcSetUp(uint16_t RegConf0,uint16_t RegConf1){
	/*
	 * RefConf0 configure: Voltaje of Reference (Extern/intern Or Vcc)
	 * RefConf1 configure: Channel(s) to convert and/or sequences
	 */
	bitLow(ADC10CTL0,ENC);
	ADC10CTL1 = SingleChannelSingleConversion + ADC10CLKSorce_ADCOsc + ADC10CLKDivBy_1 + RegConf1;
	ADC10CTL0 = ADC10ON + ENC + SHTime_4CLKs + VRefSupVcc_VRefInfVss + RegConf0;
}

void adcOn(){
	bitHigh(ADC10CTL0,ADC10ON);
}
void adcOff(){
	bitLow(ADC10CTL0,ENC);
	bitLow(ADC10CTL0,ADC10ON);
}

void adcEnaInterrupt(){
	bitLow(ADC10CTL0,ENC);
	bitHigh(ADC10CTL0,ADC10IE);
	bitHigh(ADC10CTL0,ENC);
}
void adcDisInterrupt(){
	bitLow(ADC10CTL0,ADC10IE);
}
uint8_t adcFlagInterruptRead(){
	return ((uint8_t) ADC10CTL0 & ADC10IFG);
}
void adcFlagInterruptClear(){
	ADC10CTL0 &= ~(ADC10IFG);
}


void adcEnaAnalogInput(uint8_t PinsSeleted){
	bitHigh(ADC10AE0,PinsSeleted);
}
void adcDisAnalogInput(uint8_t PinsSeleted){
	bitLow(ADC10AE0,PinsSeleted);
}

void adcStart(uint16_t adcChannel){
	ADC10CTL1=adcChannel;
	bitHigh(ADC10CTL0,ENC+ADC10SC);
}
uint16_t adcRead(uint16_t adcChannel){
	bitLow(ADC10CTL0,ENC);
	ADC10CTL1=adcChannel;
	bitHigh(ADC10CTL0,ENC+ADC10SC);
	while(ADC10CTL1 & ADC10BUSY);
	return (ADC10MEM);
}
uint16_t adcReadLast(){
	return (ADC10MEM);
}

void adcSelectChannels(uint16_t adcChannel){
	bitLow(ADC10CTL0,ENC);
	ADC10CTL1 = SingleChannelSingleConversion + ADC10CLKSorce_ADCOsc + ADC10CLKDivBy_1 + adcChannel;
	bitHigh(ADC10CTL0,ENC);
}

void adcUseInternalRef(uint16_t RegRefMask){
	bitLow(ADC10CTL0,ENC);
	ADC10CTL0 = ADC10ON + RefInternal_On + RegRefMask + VRefSupInternal_VRefInfVss;
}
void adcUseExternalRef(uint16_t RegRefMask){
	bitLow(ADC10CTL0,ENC);
	ADC10CTL0 = ADC10ON + RefInternal_Off + RegRefMask;
}

float adcGetTempSensorInCelsius(){
	//Temperature Sensor needs Internal 1.5V Reference
	float temperature = 0.00;
	delay_cycles(35*usec);
	adcUseInternalRef(RefInternalIs1_5V + SHTime_64CLKs);//0.4126320423=1.5/(2^10*0.00355);
	temperature = (((adcRead(ChannelTempSensor)) * 0.41303539713) - 277.7465);
	return temperature;
}



uint16_t adcGetTempSensor(){
	//Temperature Sensor needs Internal 1.5V Reference
	delay_cycles(35*usec);
	adcUseInternalRef(RefInternalIs1_5V + SHTime_64CLKs);
	return (adcRead(ChannelTempSensor));
}
