/**
* @file       util.h
* @copyright  Copyright (C) 2021 Hydratech. All rights reserved.
* @license    This project is released under the Hydratech License.
* @version    01.00.00
* @date       2021-08-13
* @author     Thuan Le
* @brief      Module to handle misc functions
* @note       None
* @example    None
*/

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __UTIL_H
#define __UTIL_H

/* Includes ----------------------------------------------------------- */
#include "bsp.h"

/* Public defines ----------------------------------------------------- */
#define LOW_BYTE(word)                    (word & 0x00FF)
#define HIGH_BYTE(word)                   (word >> 8)

#define BIT_SET(value, bit)               ((value) |= (1UL << (bit)))
#define BIT_CLEAR(value, bit)             ((value) &= ~(1UL << (bit)))

#define BIT_WRITE(value, bit, bit_value)  (bit_value ? BIT_SET(value, bit) : BIT_CLEAR(value, bit))
#define BIT_READ(value, bit)              (((value) >> (bit)) & 0x01)

/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Processor-independent CRC-16 calculation.
 *                Polynomial: x^16 + x^15 + x^2 + 1 (0xA001)<br>
 *                Initial value: 0xFFFF
 *                This CRC is normally used in disk-drive controllers.
 * 
 * @param[in]     crc
 * @param[in]     a
 *
 * @return        Calculated CRC (0x0000..0xFFFF)
 */
static uint16_t util_crc16_update(uint16_t crc, uint8_t a)
{
  int i;

  crc ^= a;
  for (i = 0; i < 8; ++i)
  {
    if (crc & 1)
      crc = (crc >> 1) ^ 0xA001;
    else
      crc = (crc >> 1);
  }

  return crc;
}

static inline uint16_t util_word(uint8_t h_byte, uint8_t l_byte)
{
  uint16_t word;
  
  word = (uint16_t)(h_byte << 8);
  word = word + l_byte;

  return word;
}

#endif /* __UTIL_H */

/* End of file -------------------------------------------------------- */
