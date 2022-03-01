/*
 * adc.h
 *
 *  Created on: Mar 01, 2022
 *      Author: Shea and Darian
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"


#define SHIFT_REGISTER_DATA_PIN GPIO_Pin_6
#define SHIFT_REGISTER_CLOCK_PIN GPIO_Pin_7
#define SHIFT_REGISTER_RESET_PIN GPIO_Pin_8

#define ADC_PERIPHERAL RCC_AHB1Periph_GPIOC
#define ADC_PORT GPIOC

void initialize_adc();


#endif /* ADC_H_ */
