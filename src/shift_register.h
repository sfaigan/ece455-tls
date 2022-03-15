/*
 * shift_register.h
 *
 *  Created on: Feb 16, 2022
 *      Author: Shea and Darian
 */

#ifndef SHIFT_REGISTER_H_
#define SHIFT_REGISTER_H_

/* Includes */
#include "stm32f4xx.h"
#include "bits.h"

/* Macros */
#define SHIFT_REGISTER_DATA_PIN GPIO_Pin_6
#define SHIFT_REGISTER_CLOCK_PIN GPIO_Pin_7
#define SHIFT_REGISTER_RESET_PIN GPIO_Pin_8

#define SHIFT_REGISTER_PERIPHERAL RCC_AHB1Periph_GPIOC
#define SHIFT_REGISTER_PORT GPIOC

/* Function declarations */
void vInitializeShiftRegister();
void vSetShiftRegister( uint32_t ulData, uint8_t ucN );

#endif /* SHIFT_REGISTER_H_ */
