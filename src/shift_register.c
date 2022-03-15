/*
 * shift_register.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Shea and Darian
 */

#include "shift_register.h"

/* Initializes the shift register */
void vInitializeShiftRegister()
{
    /* Enable the GPIO_Shift_Register Clock */
    RCC_AHB1PeriphClockCmd(SHIFT_REGISTER_PERIPHERAL, ENABLE);

    /* Configure Shift Register */
    GPIO_InitTypeDef xShiftInit;
    xShiftInit.GPIO_Pin = SHIFT_REGISTER_RESET_PIN | SHIFT_REGISTER_CLOCK_PIN | SHIFT_REGISTER_DATA_PIN;
    xShiftInit.GPIO_Mode = GPIO_Mode_OUT;
    xShiftInit.GPIO_OType = GPIO_OType_PP;
    xShiftInit.GPIO_PuPd = GPIO_PuPd_NOPULL;
    xShiftInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( SHIFT_REGISTER_PORT, &xShiftInit );
}

/* Clears the shift register */
void vClearShiftRegister()
{
    GPIO_ResetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_RESET_PIN);
    GPIO_SetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_RESET_PIN);
}

/* Sets the shift register to the first N bits of ulData */
void vSetShiftRegister( uint32_t ulData, uint8_t ucN )
{
    uint8_t bit, i;
    vClearShiftRegister();
    for (i = 0; i < n; i++) {
        bit = ucGetNthBit(data, i);
        GPIO_ResetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);
        if (bit == 1) {
            GPIO_SetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);
        }
        GPIO_SetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
        GPIO_ResetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
    }
}
