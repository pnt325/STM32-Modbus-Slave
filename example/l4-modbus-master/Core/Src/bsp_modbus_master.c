
/**
 * @file       bsp_modbus_master.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2022-05-22
 * @author     Thuan Le
 * @brief      Board Support Package Modbus Master
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_modbus_master.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
modbus_master_t mb_master[BSP_MODBUS_NUM];
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef hlpuart1;

/* Private function prototypes ---------------------------------------- */
static void bsp_uart_transmit(void* param)
{
	modbus_master_t* master = (modbus_master_t*)param;

	  __HAL_UART_DISABLE_IT(master->uart, UART_IT_TXE); // Disable transmit complete interrupts
	  __HAL_UART_ENABLE_IT(master->uart, UART_IT_TC);   // Enable transmit complete interrupts
}
/* Function definitions ----------------------------------------------- */
void bsp_modbus_master_init(void)
{
	mb_master[BSP_MODBUS_1].bsp_get_tick = bsp_get_tick;
	mb_master[BSP_MODBUS_1].bsp_uart_start_transmit = bsp_uart_transmit;
	mb_master[BSP_MODBUS_1].tx_complete_req = false;
	mb_master[BSP_MODBUS_1].uart = &huart1;

	mb_master[BSP_MODBUS_2].bsp_get_tick = bsp_get_tick;
	mb_master[BSP_MODBUS_2].bsp_uart_start_transmit = bsp_uart_transmit;
	mb_master[BSP_MODBUS_2].tx_complete_req = false;
	mb_master[BSP_MODBUS_2].uart = &hlpuart1;

  modbus_master_init(&mb_master[BSP_MODBUS_1]);
  modbus_master_init(&mb_master[BSP_MODBUS_2]);
}

uint16_t bsp_modbus_master_get_response_buffer(bsp_modbus_master_t master, uint8_t index)
{
  return modbus_master_get_response_buffer(&mb_master[master], index);
}

void bsp_modbus_master_clear_response_buffer(bsp_modbus_master_t master)
{
	modbus_master_clear_response_buffer(&mb_master[master]);
}

void bsp_modbus_master_set_transmit_buffer(bsp_modbus_master_t master, uint8_t index, uint16_t value)
{
  modbus_master_set_transmit_buffer(&mb_master[master], index, value);
}

void bsp_modbus_master_clear_transmit_buffer(bsp_modbus_master_t master)
{
  modbus_master_clear_transmit_buffer(&mb_master[master]);
}

uint8_t bsp_modbus_master_read_input_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
 return modbus_master_read_input_register(&mb_master[master], slave_id, read_addr, size);
}

uint8_t bsp_modbus_master_read_coils(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
  return modbus_master_read_coils(&mb_master[master], slave_id, read_addr, size);
}

uint8_t bsp_modbus_master_read_discrete_input(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
  return modbus_master_read_discrete_input(&mb_master[master], slave_id, read_addr, size);
}

uint8_t bsp_modbus_master_read_holding_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
  return modbus_master_read_holding_register(&mb_master[master], slave_id, read_addr, size);
}

uint8_t bsp_modbus_master_write_single_coil(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint8_t state)
{
  return modbus_master_write_single_coil(&mb_master[master], slave_id, write_addr, state);
}

uint8_t bsp_modbus_master_write_single_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint16_t value)
{
  return modbus_master_write_single_register(&mb_master[master], slave_id, write_addr, value);
}

uint8_t bsp_modbus_master_write_mutiple_coils(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint16_t size)
{
  return modbus_master_write_mutiple_coils(&mb_master[master], slave_id, write_addr, size);
}

uint8_t bsp_modbus_master_write_mutiple_register(bsp_modbus_master_t master,uint8_t slave_id, uint16_t write_addr, uint16_t size)
{
  return modbus_master_write_mutiple_register(&mb_master[master], slave_id, write_addr, size);
}

uint8_t bsp_modbus_master_mask_write_register(bsp_modbus_master_t master, uint8_t slave_id, uint16_t write_addr, uint16_t and_mask, uint16_t or_mask)
{
  return modbus_master_mask_write_register(&mb_master[master], slave_id, write_addr, and_mask, or_mask);
}

uint8_t bsp_modbus_master_read_mutiple_registers(bsp_modbus_master_t master, uint8_t slave_id, uint16_t read_addr, uint16_t read_size, uint16_t write_addr, uint16_t write_size)
{
  return modbus_master_read_mutiple_registers(&mb_master[master], slave_id, read_addr, read_size, write_addr, write_size);
}

void bsp_modbus_master_rx_irq(UART_HandleTypeDef *uart) {
	if (uart == NULL) {
		return;
	}

	for (uint8_t i; i < BSP_MODBUS_NUM; i++) {
		if (mb_master[i].uart == uart) {
			modbus_master_rx_irq(&mb_master[i]);
		}
	}
}

void bsp_modbus_master_tx_irq(UART_HandleTypeDef* uart)
{
	if (uart == NULL) {
		return;
	}

	for (uint8_t i; i < BSP_MODBUS_NUM; i++) {
		if (mb_master[i].uart == uart) {
			modbus_master_tx_irq(&mb_master[i]);
		}
	}
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
