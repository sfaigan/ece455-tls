/*
 * led.c
 *
 *  Created on: Mar 01, 2022
 *      Author: Shea and Darian
 */

#include "led.h"


void initialize_led() {
    // GPIO Clock
    RCC_AHB1PeriphClockCmd(LED_PERIPHERAL, ENABLE);
    
    GPIO_InitTypeDef led_init;

	// Change to constants ! !
	led_init.GPIO_Pin = RED_LIGHT_PIN | AMBER_LIGHT_PIN | GREEN_LIGHT_PIN;
	led_init.GPIO_Mode = GPIO_Mode_Out;
	led_init.GPIO_OType = GPIO_OType_PP;
	led_init.GPIO_PuPd = GPIO_PuPd_NOPULL; // Could change to pull down?
	GPIO_Init(GPIOC, &led_init);	
}
