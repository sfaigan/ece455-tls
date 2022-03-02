/*
 * bits.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Shea and Darian
 */

#include <stdint.h>

uint8_t get_nth_bit(uint32_t data, uint8_t n) {
	return (data & ( 1 << n )) >> n;
}
