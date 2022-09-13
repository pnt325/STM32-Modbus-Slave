/*
 * test_lpuart.c
 *
 *  Created on: Sep 11, 2022
 *      Author: phatn
 */

#include <string.h>
#include "test_lpuart.h"
#include "usart.h"
#include "stm32l4xx_hal_uart_ex.h"
#include "main.h"
#include "../../lib/mb_log.h"

static uint8_t rxbuf1[128];
static uint8_t rxbuf2[128];


void test_lpuart_init(void)
{
	// HAL_UARTEx_ReceiveToIdle_DMA(&hlpuart1, rxbuf, 128);
	//__HAL_DMA_DISABLE_IT(&hlpuart1, DMA_IT_HT);	// Disable half transfer complete IT
	// HAL_UART_Receive_IT(&hlpuart1, rxbuf, 1);
//	 HAL_UART_Receive_DMA(&hlpuart1, rxbuf, 128);
	 HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxbuf1, 128);
	 HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxbuf2, 128);


	// __HAL_UART_ENABLE_IT(&hlpuart1, USART_CR1_IDLEIE);
	//LPUART1->CR1 |= USART_CR1_IDLEIE;
}

void test_lpuart_handle(void)
{
	// Polling data
//	static uint32_t pos = 0;
//	static uint32_t period = 0;

//	uint32_t new_pos = __HAL_DMA_GET_COUNTER(hlpuart1.hdmarx);
//	if(pos != new_pos)
//	{
//		mb_log("Get data\n");
//		pos = new_pos;
//	}

	// transmit using dma
//	if((uint32_t)(HAL_GetTick() - period) >= 1000)
//	{
//		HAL_UART_Transmit_DMA(&hlpuart1, "Hello\r\n", strlen("Hello\r\n"));
//		period = HAL_GetTick();
//	}


}

// __used void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
// {
// 	if(huart == &huart1)
// 	{
// 		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxbuf1, 128);
// 		mb_log("uart1 received: %d\n", Size);
// 	}

// 	if(huart == &huart2)
// 	{
// 		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, rxbuf2, 128);
// 		mb_log("uart2 recevied: %d\n", Size);
// 	}
// }


//__used void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//
//}

