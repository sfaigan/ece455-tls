/*
 * bits.h
 *
 *  Created on: Mar 2, 2022
 *      Author: Shea and Darian
 */

#ifndef BITS_H_
#define BITS_H_

/* Function declarations */
uint8_t ucGetNthBit( uint32_t ulData, uint8_t ucN );
uint32_t ulSetNthBit( uint32_t ulData, uint8_t ucN );
uint8_t ucAreNBitsFree( uint32_t ulData, uint8_t ucStart, uint8_t ucN );
uint32_t ulGetBitsInRange( uint32_t ulData, uint8_t ucFirst, uint8_t ucLast );

#endif /* BITS_H_ */
