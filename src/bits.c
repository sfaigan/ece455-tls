/*
 * bits.c
 *
 *  Created on: Feb 16, 2022
 *      Author: Shea and Darian
 */

#include <stdint.h>

/* Returns the Nth bit from a 32-bit unsigned integer */
uint8_t ucGetNthBit( uint32_t ulData, uint8_t ucN )
{
    return (ulData & ( 1 << ucN )) >> ucN;
}

/* Sets the Nth bit of a 32-bit unsigned integer */
uint32_t ulSetNthBit( uint32_t ulData, uint8_t ucN )
{
    return ulData | (1U << ucN);
}

/* Returns whether the leftmost N bits are free in a 32-bit unsigned integer */
uint8_t ucAreNBitsFree( uint32_t ulData, uint8_t ucStart, uint8_t ucN )
{
    for (int counter = ucStart; counter > ucStart-ucN; counter--)
    {
        if (ucGetNthBit(ulData, counter))
        {
            return 0;
        }
    }
    return 1;
}

/* Returns the bits in range [ucFirst, ucLast] from an unsigned 32-bit integer */
uint32_t ulGetBitsInRange( uint32_t ulData, uint8_t ucFirst, uint8_t ucLast )
{
    uint32_t ulNBits = 0;
    uint8_t ucBit;
    for (uint8_t ucCounter = ucFirst; ucCounter <= ucLast; ucCounter++)
    {
        ucBit = ucGetNthBit(ulData, ucCounter);
        if (ucBit)
        {
            ulNBits = ulSetNthBit(ulNBits, ucCounter);
        }
    }
    return ulNBits;
}
