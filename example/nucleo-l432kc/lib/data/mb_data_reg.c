/*
 * mb_data_reg.c
 *
 *  Created on: Jun 11, 2022
 *      Author: phatn
 */

#include "../../lib/data/mb_data_reg.h"

#include "../../lib/mb_assert.h"
#include "../../lib/mb_log.h"

static void     _reg_set(mb_data_reg_t* reg, uint16_t addr, uint16_t value);
static uint16_t _reg_get(mb_data_reg_t* reg, uint16_t addr);

void mb_data_reg_init(mb_data_reg_t* reg, uint16_t* data, uint16_t nreg)
{
	mb_assert(reg);
	mb_assert(data);
	mb_assert(nreg);

	reg->data = data;
	reg->nreg = nreg;
	reg->get  = _reg_get;
	reg->set  = _reg_set;
}

static void _reg_set(mb_data_reg_t *reg, uint16_t addr, uint16_t value) {
	mb_assert(reg);
	mb_assert(addr < reg->nreg);
	reg->data[addr] = value;
}

static uint16_t _reg_get(mb_data_reg_t *reg, uint16_t addr) {
	mb_assert(reg);
	mb_assert(addr < reg->nreg);
	
	return reg->data[addr];
}
