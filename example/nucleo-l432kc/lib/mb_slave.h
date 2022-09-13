/*
 * mb_slave.h
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#ifndef MB_SLAVE_H_
#define MB_SLAVE_H_

/* include ====================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "mb_stm32_include.h"
#include "ring_buffer.h"
#include "mb_buffer.h"
#include "data/mb_data.h"

/* type =======================================================*/
typedef enum
{
	MB_SUCCESS,
	MB_FAILURE
} mb_return_t;

typedef struct
{
	volatile bool     on_tx;				// On TX state
	volatile uint16_t tx_len;				// number of data on TX
	uint16_t          head;					// Add data index
	uint16_t          tail;					// Get data index
	uint8_t           data[MB_TX_BUF_SIZE]; // Data payload
} mb_tx_buf_t;

/**
 * MODBUS slave handle
 */
typedef struct
{
	void 		*uart; 		// Point to UART
	mb_buffer_t buf;		    // MODBUS buffer handle
	uint8_t     slave_addr;	// MODBUS slave address
	bool        is_init;		// MODBUS initialize flag
	mb_data_t   *data;		// MODBUS data reg
	mb_tx_buf_t tx_buf;		// MODBSU tx buffer
} mb_slave_t;

/**
 * @brief Initialize
 *
 * @param	mb 				mb_slave_t
 * @param	sl_addr			Slave address
 * @return 	mb_return_t enum value
 */
mb_return_t mb_slave_init(mb_slave_t* mb, mb_data_t* data, uint8_t sl_addr, uint32_t speed);

/**
 * @brief De-Initialize
 * 
 * @param mb 	mb_slave_t
 * 
 * @return 	mb_return_t enum value
 */
mb_return_t mb_slave_deinit(mb_slave_t* mb);

/**
 * @brief MODBUS slave handle
 * @param mb mb_slave_t
 */
void mb_slave_poll(mb_slave_t* mb);

/**
 * @brief	Modbus slave transmit message interrupt process
 * @param	mb		mb_slave_t
 */
void _mb_slave_tx_irq(mb_slave_t* mb);

/**
 * @brief 	Modbus slave received message interrupt process
 * @param	mb 		mb_slave_t
 * @param	len		Number of byte received
 */
void _mb_slave_rx_irq(mb_slave_t* mb, uint16_t len);

#endif /* MB_SLAVE_H_ */
