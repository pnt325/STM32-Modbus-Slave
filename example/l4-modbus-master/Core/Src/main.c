/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "display.h"
#include "u8g2/u8g2.h"


#include "bsp_modbus_master.h"
#include "bsp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 I2C_HandleTypeDef hi2c3;

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */


uint8_t Uart1_RxBuffer = 0;  // modbus test vars
uint8_t Uart1_TxBuffer = 0;
uint16_t data[32];
char buffer[128];
int len;
float temp = 53.8;
float V1N = 0, V2N = 0, V3N = 0, VAvg = 0;
uint16_t vars [3];
uint16_t Error = 0;




uint8_t update=0;

uint8_t recvd_data;
uint8_t flag = 0;

char *tot = "1234567.89";
char *tph = "1234";
char *fpm = "567";


volatile uint32_t pulse_capture[2] = {0};


struct {
		   uint32_t milli_sec;
		   uint32_t screen_update;
		   uint16_t keypad_scan;
		   uint32_t keypress;
		   uint32_t zero_cal;

		} Timer;


uint8_t test_mess=0;
uint8_t count=1;


							uint8_t pulse_flag =0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_LPUART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void test2(void);
void test3(void);
void send_multiple_register(void);
void send_single_register(uint16_t reg,uint16_t data);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C3_Init();
  MX_USART1_UART_Init();
  MX_LPUART1_UART_Init();
  /* USER CODE BEGIN 2 */


  HAL_UART_Receive_IT(&huart1, &Uart1_RxBuffer, 1);

  bsp_modbus_master_init();

  HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);

  extern uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
  //extern uint8_t u8x8_byte_stm32_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
  extern uint8_t u8x8_byte_stm32_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

 static u8g2_t u8g2;


/*
  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_stm32_hw_i2c, u8x8_stm32_gpio_and_delay);

  u8g2_InitDisplay(&u8g2);
  	u8g2_SetPowerSave(&u8g2, 0);
  	HAL_Delay(1);
*/



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	   //  send_single_register(0x0001,1);
	    // send_single_register(0x0002,2);
	     //send_single_register(0x0003,3);


	    // HAL_Delay(2000);
	     // send_multiple_register();
	  send_single_register(0x0000,1);
	      HAL_Delay(250);


	      	//     send_single_register(0x0002,0);
	      	  //   send_single_register(0x0003,0);
	     //test3();
	    modbus_test();




//(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t value)
//bsp_modbus_master_read_input_register(0x01, 0x0000, 0x0008) == 0x00)
  } //while

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x00300F33;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }

  /** I2C Fast mode Plus enable
  */
  HAL_I2CEx_EnableFastModePlus(I2C_FASTMODEPLUS_I2C3);
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 38400;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD3_Pin */
  GPIO_InitStruct.Pin = LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD3_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void send_single_register(uint16_t reg,uint16_t data)
{
	//bsp_rs485_enable_receive(false);
	//bsp_rs485_enable_transmit(true);

	// slave_id: 0x01
    	// write_addr: 0x0000
    	// value: 14
	if (bsp_modbus_master_write_single_register(0x01, reg, data) == 0x00)
  	{
 		// Write success

  	}
  	else
  	{
    		// Write error
  	}
}

void send_multiple_register(void)
{
	//bsp_rs485_enable_receive(false);
	//bsp_rs485_enable_transmit(true);

	// Prepare transmit data
	bsp_modbus_master_set_transmit_buffer(0, 222);
	bsp_modbus_master_set_transmit_buffer(1, 111);
	bsp_modbus_master_set_transmit_buffer(2, 300);


    	// slave_id: 0x01
    	// write_addr: 0x0000
    	// size: 3
	if (bsp_modbus_master_write_mutiple_register(0x01, 0x0000, 3) == 0x00)
  	{
 		// Write success
  	}
  	else
  	{
    		// Write error
  	}
}
void test2(void)
{
//	char display_out[20];
  uint32_t temp = 0;

 // bsp_rs485_enable_receive(false);
 // bsp_rs485_enable_transmit(true);
  if (bsp_modbus_master_read_input_register(0x01, 0x0000, 0x0008) == 0x00)
  {
    data[0] = bsp_modbus_master_get_response_buffer(0);
    data[1] = bsp_modbus_master_get_response_buffer(1);
    data[2] = bsp_modbus_master_get_response_buffer(2);
    data[3] = bsp_modbus_master_get_response_buffer(3);
    data[4] = bsp_modbus_master_get_response_buffer(4);
    data[5] = bsp_modbus_master_get_response_buffer(5);
    data[6] = bsp_modbus_master_get_response_buffer(6);
    data[7] = bsp_modbus_master_get_response_buffer(7);
  }
  else
  {
    Error++;
  }
  /*
  temp = data[3] | 0x00000000;
    temp = data[2] | (temp << 16);
    V2N = *(float *)&temp;



  temp = data[1] | 0x00000000;
  temp = data[0] | (temp << 16);
  V1N = *(float *)&temp;



  temp = data[5] | 0x00000000;
  temp = data[4] | (temp << 16);
  V3N = *(float *)&temp;

  temp = data[7] | 0x00000000;
  temp = data[6] | (temp << 16);
  VAvg = *(float *)&temp;

  sprintf(buffer, "V1N: %3.2f VAC - V2N: %3.2f VAC - V3N: %3.2f VAC - VAvg: %3.2f VAC - ResDelay: 200ms - Error: %d\r\n", V1N, V2N, V3N, VAvg, Error);
  len = strlen(buffer);
  HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, 100);
  */



  HAL_Delay(1000);
}



void test3(void)
{
  uint32_t temp = 0;
  data[0] = 0;
 	     data[1] = 0;
 	     data[2] = 0;
 	     data[3] = 0;
 	     data[4] = 0;
 	     data[5] = 0;
 	     data[6] = 0;
 	     data[7] = 0;
  //bsp_rs485_enable_receive(false);
  //bsp_rs485_enable_transmit(true);
  if (bsp_modbus_master_read_holding_register(0x01, 0x0000, 0x0003) == 0x00)
  {
    data[0] = bsp_modbus_master_get_response_buffer(0);
    data[1] = bsp_modbus_master_get_response_buffer(1);
    data[2] = bsp_modbus_master_get_response_buffer(2);
    //data[3] = bsp_modbus_master_get_response_buffer(3);
   // data[4] = bsp_modbus_master_get_response_buffer(4);
    //data[5] = bsp_modbus_master_get_response_buffer(5);
    //data[6] = bsp_modbus_master_get_response_buffer(6);
    //data[7] = bsp_modbus_master_get_response_buffer(7);
  }
  else
  {
    Error++;
  }
  vars[0]=data[0];
  vars[1]= data[1];
  vars[2]=data[2];

/*
  temp = data[1] | 0x00000000;
  temp = data[0] | (temp << 16);
  V1N = *(float *)&temp;

  temp = data[3] | 0x00000000;
  temp = data[2] | (temp << 16);
  V2N = *(float *)&temp;

  temp = data[5] | 0x00000000;
  temp = data[4] | (temp << 16);
  V3N = *(float *)&temp;

  temp = data[7] | 0x00000000;
  temp = data[6] | (temp << 16);
  VAvg = *(float *)&temp;
*/

  //len = strlen(buffer);
  //HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, 100);

  //HAL_Delay(200);
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == huart1.Instance)
  {HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
    HAL_UART_Receive_IT(&huart1, &Uart1_RxBuffer, 1);
    if (Queue_IsFull(&modbus_master_rx_queue) == 0)
      Queue_EnQueue(&modbus_master_rx_queue, Uart1_RxBuffer);
  }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == huart1.Instance)
  {
    if (Queue_IsEmpty(&modbus_master_tx_queue) == 1)
    {
      modbus_complete_transmit_req = true;
      //bsp_rs485_enable_receive(true);
    }
    else
    {
      Uart1_TxBuffer = Queue_DeQueue(&modbus_master_tx_queue);
      HAL_UART_Transmit_IT(&huart1, &Uart1_TxBuffer, 1);
    }
  }
}



void SysTick_CallBack(void)
{

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
