/*
 * mb_crc.h
 *
 *  Created on: Jun 10, 2022
 *      Author: phatn
 */

#ifndef MB_CRC_H_
#define MB_CRC_H_

#include <stdint.h>

uint16_t mb_crc_calc(uint8_t* data, uint16_t len);

#endif /* MB_CRC_H_ */
