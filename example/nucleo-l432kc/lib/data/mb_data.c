/*
 * mb_data.c
 *
 *  Created on: Jun 11, 2022
 *      Author: phatn
 */

#include "../../lib/data/mb_data.h"

#include <string.h>

#include "../../lib/data/mb_data_config.h"
#include "../../lib/mb_assert.h"
#include "../../lib/mb_log.h"

static uint8_t  coil_db[MB_COIL_NUM/8];
static uint8_t  input_db[MB_INPUT_NUM/8];
static uint16_t reg_input_db[MB_REG_INPUT_NUM];
static uint16_t reg_holding_db[MB_REG_HOLDING_NUM];

void mb_data_init(mb_data_t* mb_data)
{
	mb_assert(mb_data);

	memset(coil_db       , 0, sizeof(coil_db));
	memset(input_db      , 0, sizeof(input_db));
	memset(reg_input_db  , 0, sizeof(reg_input_db));
	memset(reg_holding_db, 0, sizeof(reg_holding_db));

	mb_data_bit_init(&mb_data->coil       , coil_db       , MB_COIL_NUM);
	mb_data_bit_init(&mb_data->input      , input_db      , MB_INPUT_NUM);
	mb_data_reg_init(&mb_data->reg_input  , reg_input_db  , MB_REG_INPUT_NUM);
	mb_data_reg_init(&mb_data->reg_holding, reg_holding_db, MB_REG_HOLDING_NUM);
}
