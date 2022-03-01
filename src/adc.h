/*
 * adc.h
 *
 *  Created on: Mar 01, 2022
 *      Author: Shea and Darian
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx_adc.h"


#define POTENTIOMETER_PIN GPIO_Pin_3

#define ADC_PERIPHERAL RCC_AHB1Periph_GPIOC
#define ADC_CLOCK_PERIPHERAL RCC_APB2Periph_ADC1
#define ADC_PORT GPIOC

void initialize_adc();


#endif /* ADC_H_ */
