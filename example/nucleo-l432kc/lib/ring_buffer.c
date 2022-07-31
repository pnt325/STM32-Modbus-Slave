/*
 * mb_buffer.c
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#include <stdio.h>
#include "mb_assert.h"
#include "mb_log.h"
#include "ring_buffer.h"

static void     _add(ring_buffer_t *buf, uint8_t data);
static void     _get(ring_buffer_t *buf, uint8_t *obuf, uint16_t *buf_size);
static void     _flush(ring_buffer_t *buf);
static uint16_t _available(ring_buffer_t *buf);

void ring_buffer_init(ring_buffer_t *buf)
{
	mb_assert(buf);
	buf->__tail      = 0;
	buf->__head      = 0;
	buf->__available = 0;
	buf->overflow    = false;

	buf->add       = _add;
	buf->get_data  = _get;
	buf->available = _available;
	buf->flush     = _flush;
}

void _add(ring_buffer_t *buf, uint8_t data)
{
	mb_assert(buf);
	if (buf->overflow)
		return;

	buf->__data[buf->__head] = data;
	buf->__head = (buf->__head + 1) % RING_BUFFER_SIZE;
	if (buf->__available >= RING_BUFFER_SIZE)
	{
		buf->overflow = true;
		mb_log("Ring buffer overflow\n");
	}
	else
	{
		buf->overflow = false;
		buf->__available++;
	}
}

void _flush(ring_buffer_t *buf)
{
	mb_assert(buf);
	buf->__tail      = 0;
	buf->__head      = 0;
	buf->__available = 0;
	buf->overflow    = false;
}

void _get(ring_buffer_t *buf, uint8_t *data, uint16_t *data_size)
{
	mb_assert(buf);
	mb_assert(data);
	mb_assert(*data_size);

	if (buf->__available == 0)
	{
		*data_size = 0;
		return;
	}

	uint16_t len;
	len          = (buf->__available < *data_size) ? buf->__available : *data_size;
	*data_size   = len;

	for (uint16_t i = 0; i < len; i++)
	{
		data[i]     = buf->__data[buf->__tail];
		buf->__tail = (buf->__tail + 1) % RING_BUFFER_SIZE;
	}
	buf->__available = buf->__available - len;
	buf->overflow    = false;
}

uint16_t _available(ring_buffer_t *buf)
{
	return buf->__available;
}
