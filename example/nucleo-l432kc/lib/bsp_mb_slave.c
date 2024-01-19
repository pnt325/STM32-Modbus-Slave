/*
 * bsp_mb_slave.c
 *
 *  Created on: Jun 13, 2022
 *      Author: phatn
 */

/* include ====================================================*/
#include "bsp_mb_slave.h"
#include "mb_slave.h"
#include "mb_port.h"
#include "stm32l4xx_hal.h"

/* macro ======================================================*/
#define BSP_MB_SLAVE_ID				(0x01)
#define BSP_MB_SLAVE_MAIN_SPEED		(9600)	// bps
#define BSP_MB_SLAVE_HMI_SPEED		(9600)	// bps

/* type =======================================================*/
typedef enum
{
	BSP_MODBUS_SLAVE_MAIN,	// MODBUS slave will be working with L4 Master
	BSP_MODBUS_SLAVE_HMI,	// MODBUS slave will be working with HMI touch screen
	_BSP_MODBUS_SLAVE_NUM,
}bsp_mb_slave_t;

/* UART and TIMER instance */
#define uart_instance_main	huart1
#define uart_instance_hmi	huart2
#define crc_instance		hcrc

/* private variable ===========================================*/
//static mb_slave_t __mb;			// MODBUS slave instance
static mb_data_t  __mb_data;	// MODBUS data
static mb_slave_t __slave[_BSP_MODBUS_SLAVE_NUM];

/* public variable ============================================*/
extern UART_HandleTypeDef uart_instance_main;
extern UART_HandleTypeDef uart_instance_hmi;
extern CRC_HandleTypeDef  crc_instance;

void bsp_mb_slave_init(void) {
	__slave[BSP_MODBUS_SLAVE_MAIN].uart  = &uart_instance_main;
	__slave[BSP_MODBUS_SLAVE_HMI].uart   = &uart_instance_hmi;	

	mb_data_init(&__mb_data);

	mb_slave_init(&__slave[BSP_MODBUS_SLAVE_MAIN], &__mb_data, BSP_MB_SLAVE_ID, BSP_MB_SLAVE_MAIN_SPEED);
	mb_slave_init(&__slave[BSP_MODBUS_SLAVE_HMI], &__mb_data, BSP_MB_SLAVE_ID, BSP_MB_SLAVE_HMI_SPEED);

	__HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_ERR);
}

void bsp_mb_slave_handle(void) {
	mb_slave_poll(&__slave[BSP_MODBUS_SLAVE_MAIN]);
	mb_slave_poll(&__slave[BSP_MODBUS_SLAVE_HMI]);
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

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	uint32_t get_mask = __get_PRIMASK();
	__disable_irq();

	if(huart == __slave[BSP_MODBUS_SLAVE_MAIN].uart)
	{
		_mb_slave_rx_irq(&__slave[BSP_MODBUS_SLAVE_MAIN], Size);
	}
	else if(huart == __slave[BSP_MODBUS_SLAVE_HMI].uart)
	{
		_mb_slave_rx_irq(&__slave[BSP_MODBUS_SLAVE_HMI], Size);
	}

	__set_PRIMASK(get_mask);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
//	__disable_irq();
//	while(1);
}

void mb_port_start_recv(void* uart, uint8_t* buf, uint16_t buf_size)
{
	UART_HandleTypeDef* huart = (UART_HandleTypeDef*)uart;
	HAL_UARTEx_ReceiveToIdle_DMA(huart, buf, buf_size);
}

void mb_port_start_send(void* uart, uint8_t* buf, uint16_t buf_size)
{
	UART_HandleTypeDef* huart = (UART_HandleTypeDef*)uart;
	HAL_UART_Transmit_DMA(huart, buf, buf_size);
}

uint16_t mb_port_crc_calc(uint8_t* data, uint16_t data_len)
{
	// Hardware CRC accelerator
	uint32_t val = HAL_CRC_Calculate(&hcrc, (uint32_t*)data, data_len);
	 return (uint16_t)val ^ 0x000;
}

/**
  * @brief Tx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	uint32_t get_mask = __get_PRIMASK();
	__disable_irq();

	if(huart == __slave[BSP_MODBUS_SLAVE_MAIN].uart)
	{
		_mb_slave_tx_irq(&__slave[BSP_MODBUS_SLAVE_MAIN]);
	}
	else if(huart == __slave[BSP_MODBUS_SLAVE_HMI].uart)
	{
		_mb_slave_tx_irq(&__slave[BSP_MODBUS_SLAVE_HMI]);
	}

	__set_PRIMASK(get_mask);
}
