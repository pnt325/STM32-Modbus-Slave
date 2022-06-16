/*
 * mb_data.h
 *
 *  Created on: Jun 11, 2022
 *      Author: phatn
 */

#ifndef _MB_DATA_H_
#define _MB_DATA_H_

#include <stdint.h>
#include "mb_data_bit.h"
#include "mb_data_reg.h"

typedef struct mb_data_s
{
	mb_data_bit_t coil;			// Coil
	mb_data_bit_t input;		// Discrete input
	mb_data_reg_t reg_input;	// Input reg
	mb_data_reg_t reg_holding;	// Holding reg
} mb_data_t;

void mb_data_init(mb_data_t* mb_data);

#endif /* DATA_MB_DATA_H_ */
