/*
 * mb_buffer.c
 *
 *  Created on: Jun 10, 2022
 *      Author: phatn
 */

#include "mb_buffer.h"
#include "mb_assert.h"
#include "mb_log.h"

static mb_pdu_t* _next(mb_buffer_t *buf);
static void      _commit_next(mb_buffer_t *buf);
static mb_pdu_t* _get_data(mb_buffer_t *buf);
static void      _commit_get(mb_buffer_t *buf);
static void      _flush(mb_buffer_t *buf);
static uint8_t   _available(mb_buffer_t *buf);

void mb_buffer_init(mb_buffer_t *buf) {
	mb_assert(buf);
	buf->__available = 0;
	buf->__tail      = 0;
	buf->__head      = 0;

	buf->next        = _next;
	buf->commit_next = _commit_next;
	buf->get_data    = _get_data;
	buf->commit_get  = _commit_get;
	buf->flush       = _flush;
	buf->available   = _available;
}

static mb_pdu_t* _next(mb_buffer_t *buf) {
	mb_assert(buf);
	return &buf->__data[buf->__head];
}

static void _commit_next(mb_buffer_t *buf) {
	mb_assert(buf);
	if (buf->__available >= MB_BUFFER_SIZE) {
		mb_log("MB buffer overflow\n");
		return;
	} else {
		buf->__head = (buf->__head + 1) % MB_BUFFER_SIZE;
		buf->__available++;
	}
}

static mb_pdu_t* _get_data(mb_buffer_t *buf) {
	mb_assert(buf);
	return &buf->__data[buf->__tail];
}

static void _commit_get(mb_buffer_t *buf) {
	mb_assert(buf);
	if (buf->__available) {
		buf->__tail = (buf->__tail + 1) % MB_BUFFER_SIZE;
		buf->__available--;
	}
}

static void _flush(mb_buffer_t *buf) {
	mb_assert(buf);
	buf->__tail      = 0;
	buf->__head      = 0;
	buf->__available = 0;
}

static uint8_t _available(mb_buffer_t *buf) {
	mb_assert(buf);
	
	return buf->__available;
}
