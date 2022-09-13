/*
 * mb_buffer.h
 *
 *  Created on: Jun 10, 2022
 *      Author: phatn
 */

#ifndef MB_BUFFER_H_
#define MB_BUFFER_H_

#include <stdint.h>
#include "mb_config.h"

#define MB_BUFFER_SIZE			10

/**
 * Modbus protocol data unit
 */
typedef struct {
	uint16_t len;
	uint8_t  data[MB_PDU_SIZE];
}mb_pdu_t;

typedef struct mb_buffer_t {
	/* Data structure */
	uint8_t __head;										// head index
	uint8_t __tail;										// tail index
	uint8_t __available;								// Number of data item available
	mb_pdu_t __data[MB_BUFFER_SIZE];					// Data array

	/* Handle function */
	uint8_t*  (*next)(struct mb_buffer_t* buf);		    // Get pointer to next data on buffer
	void      (*commit_next)(struct mb_buffer_t* buf, uint16_t len);	// Commit next data is set

	mb_pdu_t* (*get_data)(struct mb_buffer_t* buf);		// Get pointer of data in buffer
	void      (*commit_get)(struct mb_buffer_t* buf);	// Commit data get out of buffer

	void      (*flush)(struct mb_buffer_t* buf);		// Flush buffer
	uint8_t   (*available)(struct mb_buffer_t* buf);	// Get data available
}mb_buffer_t;

void mb_buffer_init(mb_buffer_t* buf);

#endif /* MB_BUFFER_H_ */
