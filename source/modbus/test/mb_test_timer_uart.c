/*
 * mb_test_timer_uart.c
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#include <string.h>

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_tim.h"
#include "tim.h"
#include "usart.h"

#include "../mb_config.h"

#define UART_SPEED		9600	// uart speed
#define T35				((UART_SPEED/8)/1000)

volatile uint32_t tick_count = 0;

static uint8_t recv_buf[1];

void mb_test_timer_uart(void)
{
	mb_log_init();
	HAL_UART_Receive_IT(&huart6, recv_buf, 1);
	__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
}

void mb_test_send(void)
{
#if 0
	uint8_t buf[32] = {0};
	snprintf(buf, 32, "[%u] Hello from modbus slave\n", HAL_GetTick());
	int len = strlen(buf);
	HAL_UART_Transmit(&huart6, buf, len, 100);

	HAL_Delay(1000);
#endif
}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if(htim == &htim3)
//	{
//		HAL_UART_AbortTransmit_IT(&huart6);
//
//		HAL_TIM_Base_Stop_IT(htim);
//		mb_log("Period: %u\n", HAL_GetTick());
//
//		HAL_UART_Receive_IT(&huart6, recv_buf, 1);
//	}
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	// Get the data on UART6
//	if(huart == &huart6)
//	{
//		// Restart timer
//		HAL_TIM_Base_Stop_IT(&htim3);
//		__HAL_TIM_SET_COUNTER(&htim3, 0);
//		HAL_TIM_Base_Start_IT(&htim3);
//
//		HAL_UART_Receive_IT(&huart6, recv_buf, 1);
//		mb_log("[%u]RECV: %u\n", HAL_GetTick(),recv_buf[0]);
//	}
//}




