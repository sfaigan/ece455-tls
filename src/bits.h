/*
 * bits.h
 *
 *  Created on: Mar 2, 2022
 *      Author: sfaigan
 */

#ifndef BITS_H_
#define BITS_H_

uint8_t get_nth_bit(uint32_t data, uint8_t n);
uint32_t set_nth_bit(uint32_t data, uint8_t n);
uint8_t are_n_bits_free(uint32_t data, uint8_t start, uint8_t n);

#endif /* BITS_H_ */
