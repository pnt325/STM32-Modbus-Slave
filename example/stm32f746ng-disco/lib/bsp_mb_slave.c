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
#define BSP_MB_SLAVE_SPEED			115200	// bps
#define BSP_MB_TIMER_CLOCK_SOURCE	100		// Mhz

/* type =======================================================*/
typedef enum
{
	BSP_MODBUS_SLAVE_MAIN,	// MODBUS slave will be working with L4 Master
	BSP_MODBUS_SLAVE_HMI,	// MODBUS slave will be working with HMI touch screen
	_BSP_MODBUS_SLAVE_NUM,
}bsp_mb_slave_t;

/* UART and TIMER instance */
#define uart_instance 		huart6
#define timer_instance		htim3

/* private variable ===========================================*/
static mb_slave_t __mb;			// MODBUS slave instance
static mb_data_t  __mb_data;	// MODBUS data

/* public variable ============================================*/
extern UART_HandleTypeDef uart_instance;
extern TIM_HandleTypeDef timer_instance;

void bsp_mb_slave_init(void) {
	__mb.uart = &uart_instance;
	__mb.timer = &timer_instance;

	mb_data_init(&__mb_data);
	mb_slave_init(&__mb, &__mb_data, BSP_MB_SLAVE_ID, BSP_MB_SLAVE_SPEED, BSP_MB_TIMER_CLOCK_SOURCE);
}

void bsp_mb_slave_handle(void) {
	mb_slave_handle(&__mb);
}

uint8_t bsp_mb_id_get(void) {
	return BSP_MB_SLAVE_ID;
}

void bsp_mb_coil_set(uint16_t addr, uint8_t status) {
	__mb.data->coil.set(&__mb.data->coil, addr, status);
}

uint8_t bsp_mb_coil_get(uint16_t addr) {
	return __mb.data->coil.get(&__mb.data->coil, addr);
}

void bsp_mb_discrete_input_set(uint16_t addr, uint8_t status) {
	__mb.data->input.set(&__mb.data->input, addr, status);
}

uint8_t bsp_mb_discrete_input_get(uint16_t addr) {
	return __mb.data->input.get(&__mb.data->input, addr);
}

void bsp_mb_input_reg_set(uint16_t addr, uint16_t value) {
	__mb.data->reg_input.set(&__mb.data->reg_input, addr, value);
}

uint16_t bsp_mb_input_reg_get(uint16_t addr) {
	return __mb.data->reg_input.get(&__mb.data->reg_input, addr);
}

void bsp_mb_holding_reg_set(uint16_t addr, uint16_t value) {
	__mb.data->reg_holding.set(&__mb.data->reg_holding, addr, value);
}

uint16_t bsp_mb_holding_reg_get(uint16_t addr) {
	return __mb.data->reg_holding.get(&__mb.data->reg_holding, addr);
}

/*========================================================================*/
/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(__mb.timer == htim)
	{
		_mb_slave_timer_irq(&__mb);
	}
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(__mb.uart == huart)
	{
		_mb_slave_rx_irq(&__mb);
	}
}

/**
  * @brief Tx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(__mb.uart == huart)
	{
		_mb_slave_tx_irq(&__mb);
	}
}
