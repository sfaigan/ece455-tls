/*
 * adc.c
 *
 *  Created on: Mar 01, 2022
 *      Author: Shea and Darian
 */

#include "adc.h"


void initialize_adc() {
    // GPIO Clock
    RCC_AHB1PeriphClockCmd(ADC_PERIPHERAL, ENABLE);

    // TODO: Change name of ADC_1
	ADC_InitTypeDef ADC_1;
	GPIO_InitTypeDef ADC_1_GPIO;

	// ADC GPIO Pin
 	ADC_1_GPIO.GPIO_Pin = POTENTIOMETER_PIN; // analog on pin 3
	ADC_1_GPIO.GPIO_Mode = GPIO_Mode_AN;
	ADC_1_GPIO.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_PORT, &ADC_1_GPIO);

	RCC_APB2PeriphClockCmd(ADC_CLOCK_PERIPHERAL, ENABLE); // enable adc clock

	// TODO: Verify resolution is okay
	ADC_1.ADC_Resolution = ADC_Resolution_12b;	// 12-bit
	ADC_1.ADC_ScanConvMode = DISABLE;
	ADC_1.ADC_ContinuousConvMode = ENABLE;
	ADC_1.ADC_ExternalTrigConv = DISABLE;
	ADC_1.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_1.ADC_DataAlign = ADC_DataAlign_Right;	// right align of ADC data
	ADC_1.ADC_NbrOfConversion = 1;               // one conversion at a time
	ADC_Init(ADC1, &ADC_1);

    ADC_Cmd(ADC1, ENABLE);
    // TODO: Channel 11 vs channel 1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_13 , 1, ADC_SampleTime_3Cycles);
}

uint16_t read_adc() {
	// Start conversion
	ADC_SoftwareStartConv(ADC1);

	// Wait for conversion to complete
	while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

	// Return potentiometer reading as value from 1-100
	return ADC_GetConversionValue(ADC1);
}
