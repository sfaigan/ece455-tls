/*
 * adc.c
 *
 *  Created on: Mar 01, 2022
 *      Author: Shea and Darian
 */

#include "adc.h"

void vInitializeADC()
{
    // GPIO Clock
    RCC_AHB1PeriphClockCmd(ADC_PERIPHERAL, ENABLE);

    ADC_InitTypeDef ADC_1;
    GPIO_InitTypeDef ADC_1_GPIO;

    /* ADC GPIO Pin */
    ADC_1_GPIO.GPIO_Pin = POTENTIOMETER_PIN; // analog on pin 3
    ADC_1_GPIO.GPIO_Mode = GPIO_Mode_AN;
    ADC_1_GPIO.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_PORT, &ADC_1_GPIO);

    /* Enable ADC Clock */
    RCC_APB2PeriphClockCmd(ADC_CLOCK_PERIPHERAL, ENABLE);

    /* Configure ADC */
    ADC_1.ADC_Resolution = ADC_Resolution_12b;
    ADC_1.ADC_ScanConvMode = DISABLE;
    ADC_1.ADC_ContinuousConvMode = ENABLE;
    ADC_1.ADC_ExternalTrigConv = DISABLE;
    ADC_1.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_1.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_1.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &ADC_1);

    /* Enable the ADC */
    ADC_Cmd(ADC1, ENABLE);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_13 , 1, ADC_SampleTime_3Cycles);
}

uint16_t usReadADC()
{
    /* Start ADC conversion and wait for it to complete */
    ADC_SoftwareStartConv(ADC1);
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    /* Return the converted value */
    return ADC_GetConversionValue(ADC1);
}
