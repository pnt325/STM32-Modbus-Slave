/*
 * mb_data_reg.h
 *
 *  Created on: Jun 11, 2022
 *      Author: phatn
 */

#ifndef _MB_DATA_REG_H_
#define _MB_DATA_REG_H_

#include <stdint.h>

typedef struct mb_data_reg_s
{
	uint16_t *data;		// Data array
	uint16_t nreg;		// Number of registor

	/**
	 * @brief Set value
	 * @param reg mb_data_reg_t
	 * @param addr address of reg
	 * @param value reg value
	 */
	void(*set)(struct mb_data_reg_s* reg, uint16_t addr, uint16_t value);

	/**
	 * @brief Get value
	 * @param reg mb_data_reg_t
	 * @param addr address of reg
	 * @return reg value
	 */
	uint16_t(*get)(struct mb_data_reg_s* reg, uint16_t addr);
} mb_data_reg_t;

/**
 * @brief Init reg
 * @param reg mb_data_reg_t
 * @param nreg Number of reg
 */
void mb_data_reg_init(mb_data_reg_t* reg, uint16_t* data, uint16_t nreg);

#endif /* DATA_MB_DATA_REG_H_ */
