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

/* macro ======================================================*/


/* type =======================================================*/
typedef enum
{
	MB_SUCCESS,
	MB_FAILURE
} mb_return_t;

/**
 * MODBUS slave handle
 */
typedef struct{
	UART_HandleTypeDef *uart;		// Point to UART
	TIM_HandleTypeDef  *timer;		// Point to timer
	ring_buffer_t      uart_buf;	// UART ring ring buffer handle
	uint8_t            uart_rx;		// UART rx data
	mb_buffer_t        buf;			// MODBUS buffer handle
	uint8_t 	       slave_addr;	// MODBUS slave address
	bool               is_init;		// MODBUS initialize flag
	mb_data_t		   data;		// MODBUS data reg
}mb_slave_t;

/**
 * @brief Initialize
 *
 * @param	mb 		mb_slave_t
 * @param	sl_addr	Slave address
 * @param   timer_clk_mhz Timer clock source MHZ
 * @return 	mb_return_t enum value
 */
mb_return_t mb_slave_init(mb_slave_t* mb, uint8_t sl_addr, uint32_t speed, uint32_t timer_clk_mhz);

/**
 * @brief De-Initialize
 * 
 * @param mb mb_slave_t
 * 
 * @return 	mb_return_t enum value
 */
mb_return_t mb_slave_deinit(mb_slave_t* mb);

/**
 * @brief MODBUS slave handle
 * @param mb mb_slave_t
 */
void        mb_slave_handle(mb_slave_t* mb);


#endif /* MB_SLAVE_H_ */
