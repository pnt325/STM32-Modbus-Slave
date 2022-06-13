/*
 * bsp_mb_slave.h
 *
 *  Created on: Jun 13, 2022
 *      Author: phatn
 */

#ifndef BSP_MB_SLAVE_H_
#define BSP_MB_SLAVE_H_

#include <stdint.h>

void     bsp_mb_slave_init(void);
void     bsp_mb_slave_handle(void);
uint8_t  bsp_mb_id_get(void);
void     bsp_mb_coil_set(uint16_t addr, uint8_t status);
uint8_t  bsp_mb_coil_get(uint16_t addr);
void     bsp_mb_discrete_input_set(uint16_t addr, uint8_t status);
uint8_t  bsp_mb_discrete_input_get(uint16_t addr);
void     bsp_mb_input_reg_set(uint16_t addr, uint16_t value);
uint16_t bsp_mb_input_reg_get(uint16_t addr);
void     bsp_mb_holding_reg_set(uint16_t addr, uint16_t value);
uint16_t bsp_mb_holding_reg_get(uint16_t addr);

#endif /* BSP_MB_SLAVE_H_ */
