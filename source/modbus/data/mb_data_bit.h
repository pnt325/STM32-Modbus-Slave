/*
 * mb_data_bit.h
 *
 *  Created on: Jun 11, 2022
 *      Author: phatn
 */

#ifndef _MB_DATA_BIT_H_
#define _MB_DATA_BIT_H_

#include <stdint.h>

typedef struct mb_data_bit_s
{
	uint8_t* data;		// Hold bit data as array of byte.
	uint16_t nbit;		// Number of bit

	/**
	 * @brief Set bit value
	 * @param bit    mb_data_bit_t
	 * @param addr   Bit address
	 * @param status Bit value 0, 1
	 */
	void     (*set)(struct mb_data_bit_s* bit, uint16_t addr, uint8_t status);

	/**
	 * @brief Get bit value
	 * @param bit  mb_data_bit_t
	 * @param addr address of bit
	 * @return bit value
	 */
	uint8_t  (*get)(struct mb_data_bit_s* bit, uint16_t addr);
} mb_data_bit_t;

/**
 * @brief Init data bit
 * @param bit   mb_data_bit_t
 * @param data  data buffer
 * @param n_bit number of bit
 */
void mb_data_bit_init(mb_data_bit_t* bit, uint8_t* data, uint16_t n_bit);


#endif /* _MB_DATA_BIT_H_ */
