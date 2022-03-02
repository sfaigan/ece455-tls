/*
 * led.c
 *
 *  Created on: Mar 01, 2022
 *      Author: Shea and Darian
 */

#include "led.h"


void vInitializeLED() {
    // GPIO Clock
    RCC_AHB1PeriphClockCmd(LED_PERIPHERAL, ENABLE);
    
    GPIO_InitTypeDef led_init;

	// Change to constants ! !
	led_init.GPIO_Pin = RED_LIGHT_PIN | YELLOW_LIGHT_PIN | GREEN_LIGHT_PIN;
	led_init.GPIO_Mode = GPIO_Mode_OUT;
	led_init.GPIO_OType = GPIO_OType_PP;
	led_init.GPIO_PuPd = GPIO_PuPd_NOPULL; // Could change to pull down?
	GPIO_Init(GPIOC, &led_init);	
}


void vEnableLED(uint8_t led)	{
	uint8_t selected_led = led % 3;

	// Turn off all LEDs
	// TODO: Fix this
	GPIO_ResetBits(LED_PORT, RED_LIGHT_PIN | YELLOW_LIGHT_PIN | GREEN_LIGHT_PIN);

	switch(selected_led) {
			case 0: GPIO_SetBits(LED_PORT, RED_LIGHT_PIN);
			case 1:	GPIO_SetBits(LED_PORT, YELLOW_LIGHT_PIN);
			case 2: GPIO_SetBits(LED_PORT, GREEN_LIGHT_PIN);

	}
}
