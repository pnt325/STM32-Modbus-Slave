/**
 * @file       modbus_master.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-04-09
 * @author     Thuan Le
 * @brief      Driver support Modbus Master
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __MODBUS_MASTER_H
#define __MODBUS_MASTER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "util.h"
#include "bsp.h"
#include "queue_circle_array.h"

/* Private macros ----------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
extern volatile bool modbus_complete_transmit_req;
extern struct_queue_array modbus_master_tx_queue;
extern struct_queue_array modbus_master_rx_queue;

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Modbus master struct
 */
typedef struct
{
  uint32_t (*bsp_get_tick) (void);
  void     (*bsp_uart_start_transmit) (void);
}
modbus_master_t;

/**
 * @brief Modbus master function enum
 */
typedef enum
{
   MODBUS_FUNCTION_READ_COILS                   = (0x01) // Modbus function 0x01 Read Coils
  ,MODBUS_FUNCTION_READ_DISCRETE_INPUTS         = (0x02) // Modbus function 0x02 Read Discrete Inputs
  ,MODBUS_FUNCTION_READ_HOLDING_REGISTERS       = (0x03) // Modbus function 0x03 Read Holding Registers
  ,MODBUS_FUNCTION_READ_INPUT_REGISTERS         = (0x04) // Modbus function 0x04 Read Input Registers
  ,MODBUS_FUNCTION_WRITE_SINGLE_COIL            = (0x05) // Modbus function 0x05 Write Single Coil
  ,MODBUS_FUNCTION_WRITE_SINGLE_REGISTER        = (0x06) // Modbus function 0x06 Write Single Register
  ,MODBUS_FUNCTION_WRITE_MUTIPLE_COILS          = (0x0F) // Modbus function 0x0F Write Multiple Coils
  ,MODBUS_FUNCTION_WRITE_MUTIPLE_REGISTERS      = (0x10) // Modbus function 0x10 Write Multiple Registers
  ,MODBUS_FUNCTION_MASK_WRITE_REGISTERS         = (0x16) // Modbus function 0x16 Mask Write Register
  ,MODBUS_FUNCTION_READ_WRITE_MUTIPLE_REGISTERS = (0x17) // Modbus function 0x17 Read Write Multiple Registers
}
modbus_master_function_t;

/* Public function prototypes ----------------------------------------- */
void modbus_master_init(modbus_master_t *modbus);

uint16_t modbus_master_get_response_buffer(modbus_master_t *modbus, uint8_t index);
void modbus_master_clear_response_buffer(modbus_master_t *modbus);
void modbus_master_set_transmit_buffer(modbus_master_t *modbus, uint8_t index, uint16_t value);
void modbus_master_clear_transmit_buffer(modbus_master_t *modbus);

uint8_t modbus_master_read_coils(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t size);
uint8_t modbus_master_read_discrete_input(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t size);
uint8_t modbus_master_read_holding_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t size);
uint8_t modbus_master_read_input_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t size);
uint8_t modbus_master_write_single_coil(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint8_t state);
uint8_t modbus_master_write_single_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t value);
uint8_t modbus_master_write_mutiple_coils(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t size);
uint8_t modbus_master_write_mutiple_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t size);
uint8_t modbus_master_mask_write_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t and_mask, uint16_t or_mask);
uint8_t modbus_master_read_mutiple_registers(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t read_size,
                                            uint16_t write_addr, uint16_t write_size);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __MODBUS_MASTER_H

/* End of file -------------------------------------------------------- */
