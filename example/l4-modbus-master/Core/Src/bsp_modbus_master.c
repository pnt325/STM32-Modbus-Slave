
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
modbus_master_t modbus;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
void bsp_modbus_master_init(void)
{
  modbus.bsp_get_tick            = bsp_get_tick;
  modbus.bsp_uart_start_transmit = bsp_uart_start_transmit;
  modbus_complete_transmit_req   = false;
  
  modbus_master_init(&modbus);
}

uint16_t bsp_modbus_master_get_response_buffer(uint8_t index)
{
  return modbus_master_get_response_buffer(&modbus, index);
}

void bsp_modbus_master_clear_response_buffer(void)
{
  modbus_master_clear_response_buffer(&modbus);
}

void bsp_modbus_master_set_transmit_buffer(uint8_t index, uint16_t value)
{
  modbus_master_set_transmit_buffer(&modbus, index, value);
}

void bsp_modbus_master_clear_transmit_buffer(void)
{
  modbus_master_clear_transmit_buffer(&modbus);
}

uint8_t bsp_modbus_master_read_input_register(uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
 return modbus_master_read_input_register(&modbus, slave_id, read_addr, size);
}

uint8_t bsp_modbus_master_read_coils(uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
  return modbus_master_read_coils(&modbus, slave_id, read_addr, size);
}

uint8_t bsp_modbus_master_read_discrete_input(uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
  return modbus_master_read_discrete_input(&modbus, slave_id, read_addr, size);
}

uint8_t bsp_modbus_master_read_holding_register(uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
  return modbus_master_read_holding_register(&modbus, slave_id, read_addr, size);
}

uint8_t bsp_modbus_master_write_single_coil(uint8_t slave_id, uint16_t write_addr, uint8_t state)
{
  return modbus_master_write_single_coil(&modbus, slave_id, write_addr, state);
}

uint8_t bsp_modbus_master_write_single_register(uint8_t slave_id, uint16_t write_addr, uint16_t value)
{
  return modbus_master_write_single_register(&modbus, slave_id, write_addr, value);
}

uint8_t bsp_modbus_master_write_mutiple_coils(uint8_t slave_id, uint16_t write_addr, uint16_t size)
{
  return modbus_master_write_mutiple_coils(&modbus, slave_id, write_addr, size);
}

uint8_t bsp_modbus_master_write_mutiple_register(uint8_t slave_id, uint16_t write_addr, uint16_t size)
{
  return modbus_master_write_mutiple_register(&modbus, slave_id, write_addr, size);
}

uint8_t bsp_modbus_master_mask_write_register(uint8_t slave_id, uint16_t write_addr, uint16_t and_mask, uint16_t or_mask)
{
  return modbus_master_mask_write_register(&modbus, slave_id, write_addr, and_mask, or_mask);
}

uint8_t bsp_modbus_master_read_mutiple_registers(uint8_t slave_id, uint16_t read_addr, uint16_t read_size, uint16_t write_addr, uint16_t write_size)
{
  return modbus_master_read_mutiple_registers(&modbus, slave_id, read_addr, read_size, write_addr, write_size);
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
