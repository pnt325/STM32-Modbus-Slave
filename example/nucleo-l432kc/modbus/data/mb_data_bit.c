/*
 * mb_data_bit.c
 *
 *  Created on: Jun 11, 2022
 *      Author: phatn
 */

#include "mb_data_bit.h"
#include "../mb_log.h"
#include "../mb_assert.h"

uint8_t _get_bit(mb_data_bit_t *bit, uint16_t addr);
void _set_bit(mb_data_bit_t *bit, uint16_t addr, uint8_t status);

void mb_data_bit_init(mb_data_bit_t *bit, uint8_t *data, uint16_t n_bit)
{
	mb_assert(bit);
	mb_assert(data);
	mb_assert(n_bit);

	bit->data = data;
	bit->nbit = n_bit;
	bit->get  = _get_bit;
	bit->set  = _set_bit;
}

uint8_t _get_bit(mb_data_bit_t *bit, uint16_t addr)
{
	mb_assert(bit);
	mb_assert(addr < bit->nbit);

	uint8_t byte_index = addr / 8;
	uint8_t bit_index  = addr % 8;

	return (uint8_t)((bit->data[byte_index] >> bit_index) & 0x01);
}

void _set_bit(mb_data_bit_t *bit, uint16_t addr, uint8_t status)
{
	mb_assert(bit);
	mb_assert(addr < bit->nbit);

	uint8_t byte_index = addr / 8;
	uint8_t bit_index  = addr % 8;

	uint8_t val = 1 << bit_index;
	if (status)
		bit->data[byte_index] = (uint8_t)(bit->data[byte_index] | val);
	else
		bit->data[byte_index] = (uint8_t)(bit->data[byte_index] & (~val));
}
