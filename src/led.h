/*
 * led.h
 *
 *  Created on: Mar 01, 2022
 *      Author: Shea and Darian
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f4xx.h"

/* Macros */
#define RED_LIGHT_PIN GPIO_Pin_0
#define YELLOW_LIGHT_PIN GPIO_Pin_1
#define GREEN_LIGHT_PIN GPIO_Pin_2

#define RED_LIGHT 0
#define YELLOW_LIGHT 1
#define GREEN_LIGHT 2

#define LED_PERIPHERAL RCC_AHB1Periph_GPIOC
#define LED_PORT GPIOC

/* Function declarations */
void vInitializeLED();
void vEnableLED( uint8_t ucLED );

#endif /* LED_H_ */
