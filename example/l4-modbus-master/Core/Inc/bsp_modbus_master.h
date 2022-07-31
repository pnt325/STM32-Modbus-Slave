/**
 * @file       bsp_modbus_master.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2022-05-22
 * @author     Thuan Le
 * @brief      Board Support Package Modbus Master
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_MODBUS_MASTER_H
#define __BSP_MODBUS_MASTER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "modbus_master.h"
#include <stm32l4xx_hal_uart.h>
#include <stm32l4xx_hal_uart_ex.h>

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
	BSP_MODBUS_1,
	BSP_MODBUS_2,
	BSP_MODBUS_NUM
}bsp_modbus_master_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

void bsp_modbus_master_init(void);

uint16_t bsp_modbus_master_get_response_buffer(bsp_modbus_master_t master, uint8_t index);
void bsp_modbus_master_clear_response_buffer(bsp_modbus_master_t master);
void bsp_modbus_master_set_transmit_buffer(bsp_modbus_master_t master, uint8_t index, uint16_t value);
void bsp_modbus_master_clear_transmit_buffer(bsp_modbus_master_t master);

uint8_t bsp_modbus_master_read_coils(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t size);
uint8_t bsp_modbus_master_read_discrete_input(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t size);
uint8_t bsp_modbus_master_read_holding_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t size);
uint8_t bsp_modbus_master_read_input_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t size);
uint8_t bsp_modbus_master_write_single_coil(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint8_t state);
uint8_t bsp_modbus_master_write_single_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint16_t value);
uint8_t bsp_modbus_master_write_mutiple_coils(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint16_t size);
uint8_t bsp_modbus_master_write_mutiple_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint16_t size);
uint8_t bsp_modbus_master_mask_write_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint16_t and_mask, uint16_t or_mask);
uint8_t bsp_modbus_master_read_mutiple_registers(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t read_size,
                                                 uint16_t write_addr, uint16_t write_size);

void bsp_modbus_master_rx_irq(UART_HandleTypeDef* uart);
void bsp_modbus_master_tx_irq(UART_HandleTypeDef* uart);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_MODBUS_MASTER_H

/* End of file -------------------------------------------------------- */
