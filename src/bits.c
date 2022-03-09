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

uint32_t set_nth_bit(uint32_t data, uint8_t n) {
	return data | (1U << n);
	// return traffic |= 0b00000000000010000000000000000000;
}

uint8_t are_n_bits_free(uint32_t data, uint8_t start, uint8_t n) {
	for (int i = start; i > start-n; i--) {
		if (get_nth_bit(data, i)) {
			return 0;
		}
	}
	return 1;
}

// [first, last]
uint32_t get_bits_in_range(uint32_t data, uint8_t first, uint8_t last) {
	uint32_t n_bits = 0;
	uint8_t bit;
	for (int i = first; i <= last; i++) {
        bit = get_nth_bit(data, i);
        if (bit) {
            n_bits = set_nth_bit(n_bits, i);
        }
	}
	return n_bits;
}
