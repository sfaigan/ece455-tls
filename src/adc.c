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

	ADC_InitTypeDef ADC_1;
	GPIO_InitTypeDef ADC_1_GPIO;

	// ADC GPIO Pin
 	ADC_1_GPIO.GPIO_Pin = POTENTIOMETER_PIN; // analog on pin 3
	ADC_1_GPIO.GPIO_Mode = GPIO_Mode_AN;
	ADC_1_GPIO.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_PORT, &ADC_1_GPIO)

	RCC_APB2PeriphClockCmd(RCC_AHB2_Periph_ADC1, ENABLE); // enable adc clock

	ADC_1.ADC_Resolution = ADC_Resolution_12b;	// 12bit
	ADC_1.ADC_ScanConvMode = DISABLE;
	ADC_1.ADC_ContinuousConvMode = ENABLE;
	ADC_1.ADC_ExternalTrigConv = DISABLE;
	ADC_1.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_1.ADC_DataAlign = ADC_DataAlign_Right;	// right align of ADC data
	ADC_1.ADC_NbrOfConversion = 1;               // one conversion at a time
	ADC_init(ADC1, &ADC_1);

    ADC_Cmd(ADC1, ENABLE);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_11 , 1, ADC_SampleTime_84Cycles);
}
