/*
 * mb_buffer.h
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stdint.h>
#include <stdbool.h>

#define RING_BUFFER_SIZE		256

typedef struct ring_buffer_t
{
	uint16_t __tail;
	uint16_t __head;
	uint16_t __data[RING_BUFFER_SIZE];
	uint16_t __available;
	bool     overflow;

	/**
	 * @brief Add buffer data
	 * @param buf ring_buffer_t
	 * @param data byte data
	 */
	void    (*add)(struct ring_buffer_t* buf, uint8_t data);

	/**
	 * @brief Get buffer data
	 * @param buf ring_buffer_t
	 * @param obuf target of copy data buffer
	 * @param buf_len [in|out] the target buffer size and number of byte copied
	 */
	void    (*get_data)(struct ring_buffer_t* buf, uint8_t* obuf, uint16_t *buf_len);

	/**
	 * @brief Flush buffer
	 * @param buf ring_buffer_t
	 */
	void    (*flush)(struct ring_buffer_t* buf);

	/**
	 * @brief Get number of byte available
	 * @param buf ring_buffer_t
	 * @return number of byte
	 */
	uint16_t(*available)(struct ring_buffer_t* buf);
} ring_buffer_t;

/**
 * @brief Initialize buffer
 * @param buf mb_buffer_t
 */
void ring_buffer_init(ring_buffer_t* buf);

#endif /* RING_BUFFER_H_ */
