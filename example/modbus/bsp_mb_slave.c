/*
 * bsp_mb_slave.c
 *
 *  Created on: Jun 13, 2022
 *      Author: phatn
 */

/* include ====================================================*/
#include "bsp_mb_slave.h"
#include "mb_slave.h"

/* macro ======================================================*/
#define BSP_MB_SLAVE_ID				0x01
#define BSP_MB_SLAVE_SPEED			9600	// bps
#define BSP_MB_TIMER_CLOCK_SOURCE	80		// Mhz

/* private variable ===========================================*/
static mb_slave_t __mb;

/* public variable ============================================*/
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim2;

void bsp_mb_slave_init(void) {
	__mb.uart = &huart2;
	__mb.timer = &htim2;
	mb_slave_init(&__mb, BSP_MB_SLAVE_ID, BSP_MB_SLAVE_SPEED, BSP_MB_TIMER_CLOCK_SOURCE);
}

void bsp_mb_slave_handle(void) {
	mb_slave_handle(&__mb);
}

uint8_t bsp_mb_id_get(void) {
	return BSP_MB_SLAVE_ID;
}

void bsp_mb_coil_set(uint16_t addr, uint8_t status) {
	__mb.data.coil.set(&__mb.data.coil, addr, status);
}

uint8_t bsp_mb_coil_get(uint16_t addr) {
	return __mb.data.coil.get(&__mb.data.coil, addr);
}

void bsp_mb_discrete_input_set(uint16_t addr, uint8_t status) {
	__mb.data.input.set(&__mb.data.input, addr, status);
}

uint8_t bsp_mb_discrete_input_get(uint16_t addr) {
	return __mb.data.input.get(&__mb.data.input, addr);
}

void bsp_mb_input_reg_set(uint16_t addr, uint16_t value) {
	__mb.data.reg_input.set(&__mb.data.reg_input, addr, value);
}

uint16_t bsp_mb_input_reg_get(uint16_t addr) {
	return __mb.data.reg_input.get(&__mb.data.reg_input, addr);
}

void bsp_mb_holding_reg_set(uint16_t addr, uint16_t value) {
	__mb.data.reg_holding.set(&__mb.data.reg_holding, addr, value);
}

uint16_t bsp_mb_holding_reg_get(uint16_t addr) {
	return __mb.data.reg_holding.get(&__mb.data.reg_holding, addr);
}
