/*
 * mb_crc.c
 *
 *  Created on: Jun 10, 2022
 *      Author: phatn
 */

#include "mb_crc.h"

uint16_t mb_crc_calc(uint8_t* data, uint16_t len)
{
    unsigned int temp, temp2, flag;
    temp = 0xFFFF;
    for (uint16_t i = 0; i < len; i++)
    {
        temp = temp ^ data[i];
        for (uint8_t j = 1; j <= 8; j++)
        {
            flag = temp & 0x0001;
            temp >>=1;
            if (flag)
                temp ^= 0xA001;
        }
    }
    // Reverse byte order.
    temp2 = temp >> 8;
    temp = (temp << 8) | temp2;
    temp &= 0xFFFF;

    // the returned value is already swapped
    // crcLo byte is first & crcHi byte is last
    return temp;
}
