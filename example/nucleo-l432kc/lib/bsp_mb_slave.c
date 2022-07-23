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

/* type =======================================================*/
typedef enum
{
	BSP_MODBUS_SLAVE_MAIN,	// MODBUS slave will be working with L4 Master
	BSP_MODBUS_SLAVE_HMI,	// MODBUS slave will be working with HMI touch screen
	_BSP_MODBUS_SLAVE_NUM,
}bsp_mb_slave_t;

/* UART and TIMER instance */
#define uart_instance_main	huart1
#define uart_instance_hmi	hlpuart1
#define timer_instance_main	htim2
#define timer_instance_hmi	htim7

/* private variable ===========================================*/
//static mb_slave_t __mb;			// MODBUS slave instance
static mb_data_t  __mb_data;	// MODBUS data
static mb_slave_t __slave[_BSP_MODBUS_SLAVE_NUM];

/* public variable ============================================*/
extern UART_HandleTypeDef uart_instance_main;
extern UART_HandleTypeDef uart_instance_hmi;
extern TIM_HandleTypeDef timer_instance_main;
extern TIM_HandleTypeDef timer_instance_hmi;

void bsp_mb_slave_init(void) {
	__slave[BSP_MODBUS_SLAVE_MAIN].uart  = &uart_instance_main;
	__slave[BSP_MODBUS_SLAVE_HMI].uart   = &uart_instance_hmi;
	__slave[BSP_MODBUS_SLAVE_MAIN].timer = &timer_instance_main;
	__slave[BSP_MODBUS_SLAVE_HMI].timer  = &timer_instance_hmi;

	mb_data_init(&__mb_data);

	mb_slave_init(&__slave[BSP_MODBUS_SLAVE_MAIN], &__mb_data, BSP_MB_SLAVE_ID, BSP_MB_SLAVE_SPEED, BSP_MB_TIMER_CLOCK_SOURCE);
	mb_slave_init(&__slave[BSP_MODBUS_SLAVE_HMI], &__mb_data, BSP_MB_SLAVE_ID, BSP_MB_SLAVE_SPEED, BSP_MB_TIMER_CLOCK_SOURCE);
}

void bsp_mb_slave_handle(void) {
	mb_slave_handle(&__slave[BSP_MODBUS_SLAVE_MAIN]);
	mb_slave_handle(&__slave[BSP_MODBUS_SLAVE_MAIN]);
}

uint8_t bsp_mb_id_get(void) {
	return BSP_MB_SLAVE_ID;
}

void bsp_mb_coil_set(uint16_t addr, uint8_t status) {
	__mb_data.coil.set(&__mb_data.coil, addr, status);
}

uint8_t bsp_mb_coil_get(uint16_t addr) {
	return __mb_data.coil.get(&__mb_data.coil, addr);
}

void bsp_mb_discrete_input_set(uint16_t addr, uint8_t status) {
	__mb_data.input.set(&__mb_data.input, addr, status);
}

uint8_t bsp_mb_discrete_input_get(uint16_t addr) {
	return __mb_data.input.get(&__mb_data.input, addr);
}

void bsp_mb_input_reg_set(uint16_t addr, uint16_t value) {
	__mb_data.reg_input.set(&__mb_data.reg_input, addr, value);
}

uint16_t bsp_mb_input_reg_get(uint16_t addr) {
	return __mb_data.reg_input.get(&__mb_data.reg_input, addr);
}

void bsp_mb_holding_reg_set(uint16_t addr, uint16_t value) {
	__mb_data.reg_holding.set(&__mb_data.reg_holding, addr, value);
}

uint16_t bsp_mb_holding_reg_get(uint16_t addr) {
	return __mb_data.reg_holding.get(&__mb_data.reg_holding, addr);
}

/*========================================================================*/
/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == __slave[BSP_MODBUS_SLAVE_MAIN].timer)
	{
		_mb_slave_timer_irq(&__slave[BSP_MODBUS_SLAVE_MAIN]);
		return;
	}

	if(htim == __slave[BSP_MODBUS_SLAVE_HMI].timer)
	{
		_mb_slave_timer_irq(&__slave[BSP_MODBUS_SLAVE_HMI]);
		return;
	}
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == __slave[BSP_MODBUS_SLAVE_MAIN].uart)
	{
		_mb_slave_rx_irq(&__slave[BSP_MODBUS_SLAVE_MAIN]);
		return;
	}

	if(huart == __slave[BSP_MODBUS_SLAVE_HMI].uart)
	{
		_mb_slave_rx_irq(&__slave[BSP_MODBUS_SLAVE_HMI]);
		return;
	}
}

/**
  * @brief Tx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == __slave[BSP_MODBUS_SLAVE_MAIN].uart)
	{
		_mb_slave_tx_irq(&__slave[BSP_MODBUS_SLAVE_MAIN]);
		return;
	}

	if(huart == __slave[BSP_MODBUS_SLAVE_HMI].uart)
	{
		_mb_slave_tx_irq(&__slave[BSP_MODBUS_SLAVE_HMI]);
		return;
	}
}
