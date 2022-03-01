/*
 * shift_register.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Shea and Darian
 */

#include "shift_register.h"


void initialize_shift_register() {
	/* Enable the GPIO_Shift_Register Clock */
	RCC_AHB1PeriphClockCmd(SHIFT_REGISTER_PERIPHERAL, ENABLE);

	GPIO_InitTypeDef shift_init;

	// Change to constants ! !
	shift_init.GPIO_Pin = SHIFT_REGISTER_RESET_PIN | SHIFT_REGISTER_CLOCK_PIN | SHIFT_REGISTER_DATA_PIN;
	shift_init.GPIO_Mode = GPIO_Mode_Out;
	shift_init.GPIO_OType = GPIO_OType_PP;
	shift_init.GPIO_PuPd = GPIO_PuPd_NOPULL; // Could change to pull down?
	shift_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SHIFT_REGISTER_PORT, &shift_init);
}

uint8_t get_nth_bit(uint32_t data, uint8_t n) {
	return (data & ( 1 << n )) >> n;
}

void clear_shift_register() {
	GPIO_ResetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_RESET_PIN);
	GPIO_SetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_RESET_PIN);
}

// Sets the shift register to the first n bits of data
void set_shift_register(uint32_t data, uint8_t n) {
	uint8_t bit, i;
	clear_shift_register();
	for (i = 0; i < n; i++) {
		bit = get_nth_bit(data, i);
		GPIO_ResetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);
		if (bit == 1) {
			GPIO_SetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_DATA_PIN);
		}
		GPIO_SetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
		GPIO_ResetBits(SHIFT_REGISTER_PORT, SHIFT_REGISTER_CLOCK_PIN);
	}
}
