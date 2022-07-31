
/**
 * @file       bsp.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2022-05-22
 * @author     Thuan Le
 * @brief      Board Support Package (BSP)
 * 
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp.h"

/* Private defines ---------------------------------------------------- */
#define RS485_ENABLE_DI_PIN (GPIO_PIN_11)
#define RS485_ENABLE_RO_PIN (GPIO_PIN_12)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
extern UART_HandleTypeDef huart1;

/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
uint32_t bsp_get_tick(void)
{
  return HAL_GetTick();
}

void bsp_uart_start_transmit(void)
{
  __HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE); // Disable transmit complete interrupts
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_TC);   // Enable transmit complete interrupts
}

void bsp_rs485_enable_transmit(bool enable)
{
  if (enable)
    HAL_GPIO_WritePin(GPIOA, RS485_ENABLE_DI_PIN, GPIO_PIN_SET);
  else
    HAL_GPIO_WritePin(GPIOA, RS485_ENABLE_DI_PIN, GPIO_PIN_RESET);
}

void bsp_rs485_enable_receive(bool enable)
{
  if (enable)
  {
    HAL_GPIO_WritePin(GPIOA, RS485_ENABLE_RO_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, RS485_ENABLE_DI_PIN, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(GPIOA, RS485_ENABLE_RO_PIN, GPIO_PIN_SET);
  }
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */
