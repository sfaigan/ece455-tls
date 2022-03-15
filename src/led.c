/*
 * led.c
 *
 *  Created on: Mar 01, 2022
 *      Author: Shea and Darian
 */

#include "led.h"

/* Initialize the traffic light LEDs */
void vInitializeLED()
{
    /* Enable LED clock */
    RCC_AHB1PeriphClockCmd(LED_PERIPHERAL, ENABLE);
    
    /* Configure LEDs */
    GPIO_InitTypeDef xLEDInit;
    xLEDInit.GPIO_Pin = RED_LIGHT_PIN | YELLOW_LIGHT_PIN | GREEN_LIGHT_PIN;
    xLEDInit.GPIO_Mode = GPIO_Mode_OUT;
    xLEDInit.GPIO_OType = GPIO_OType_PP;
    xLEDInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &xLEDInit);    
}

/* Enable the given traffic light LED */
void vEnableLED( uint8_t ucLED )
{
    uint8_t ucSelectedLED = ucLED % 3;

    /* Disable all LEDs */
    GPIO_ResetBits(LED_PORT, RED_LIGHT_PIN | YELLOW_LIGHT_PIN | GREEN_LIGHT_PIN);

    /* Enable the given LED */
    switch(ucSelectedLED)
    {
        case RED_LIGHT:
            GPIO_SetBits(LED_PORT, RED_LIGHT_PIN);
            break;
        case YELLOW_LIGHT:
            GPIO_SetBits(LED_PORT, YELLOW_LIGHT_PIN);
            break;
        case GREEN_LIGHT:
            GPIO_SetBits(LED_PORT, GREEN_LIGHT_PIN);
            break;
    }
}
