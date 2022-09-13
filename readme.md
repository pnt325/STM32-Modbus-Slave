# MODBUS Slave lib for STM32

Lib write follow standard `MODBUS APPLICATION PROTOCOL SPECIFICATION
V1.1b3` publish by [modbus.org](https://modbus.org/). Download [Modbus_Application_Protocol_V1_1b3.pdf](https://modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf) or 
[doc](docs/Modbus_Application_Protocol_V1_1b3.pdf)

Lib source path: `lib`

## Configure for STM32 using CubeMX

### 1. UART

Choose UART and enable global interrupt as bellow:

![](docs/image/cube_uart.png)

Note: The modbus lib implement the get data using interrupt and ring-buffer 
it has limit of speed over UART to make sure it's working well the limit 
of speed is `115200`

### 2. Copy modbus source from `lib` to your project, like bellow:

![](docs/image/modbus_lib.png)

Modbus lib use Segger RTT for log. Default it's enabled. 

If don't use this log can disable by edit file: `lib/mb_log.h` and comment macro `MB_LOG`
```c
#ifdef MB_DEBUG
#define MB_LOG
#endif

#ifdef MB_LOG
#include "SEGGER_RTT.h"
#define mb_log_init()		SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP)
#define mb_log(_c, ...)		SEGGER_RTT_printf(0, _c, ##__VA_ARGS__);
#else
#define mb_log_init()
#define mb_log(_c, ...)
#endif
```

If keep using the Segger RTT log need to edit include on project configure like bellow:

![](docs/image/segger_rtt.png)

### 4. Include HAL lib for taraget STM32

Edit file `lib/mb_stm32_include.h`, example project run on STM32F7, if you are using other MCU should edit for suitable
```c
#ifndef MB_STM32_INCLUDE_H_
#define MB_STM32_INCLUDE_H_

#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_uart.h"
#include "stm32f7xx_hal_tim.h"

#endif /* MB_STM32_INCLUDE_H_ */

```

### 5. Note:

Modbus lib already implement the UART and Timer callback handle on `bsp_mb_slave.c`. Do not implement the interrupt callback other place to avoid error while compile


## Configure modbus lib

### 1. Modbus data register

Edit file `lib/data/mb_data_config.h` to change the limit register of data. Update the value of macro bellow:

```c
#ifndef _MB_DATA_CONFIG_H_
#define _MB_DATA_CONFIG_H_

#define MB_COIL_NUM				32	// number of coil, @note: multiple of 8, @TODO edit
#define MB_INPUT_NUM			32	// number of input, @note: multiple of 8, @TODO edit
#define MB_REG_INPUT_NUM		32	// number of reg input , @TODO edit
#define MB_REG_HOLDING_NUM		32	// number of reg holding, @TODO edit

#endif /* _MB_DATA_CONFIG_H_ */
```

### 2. MODBUS param
Edit the macro value on `lib/bsp_mb_slave.c`. UART speed like value use on `CubeMX` configure
```c
/* macro ======================================================*/
#define BSP_MB_SLAVE_ID				0x01
#define BSP_MB_SLAVE_SPEED			115200	// bps
#define BSP_MB_TIMER_CLOCK_SOURCE	100		// Mhz
```
Edit `timer` and `uart` instance on `bsp_slave.c`
```c
/* UART and TIMER instance */
#define uart_instance 		huart6
#define timer_instance		htim3
```

## Note

The lib optimize for high performance working without delay and multiple modbus request handle limit 10 request. The request can increase depend on target of application. It's require more RAM. The limit can edit on file `lib/mb_buffer.h` change value of macro `MB_BUFFER_SIZE`

```c
/* mb_buffer.h */
#define MB_BUFFER_SIZE			10
```

## Example 

Check on `main.c`

Test example, edit the value of register
```c
	// Update coil status
	bsp_mb_coil_set(0, 1);
	bsp_mb_coil_set(0, 0);
	bsp_mb_coil_set(0, 1);
	bsp_mb_coil_set(0, 0);

	// Update input register
	bsp_mb_discrete_input_set(0, 0);
	bsp_mb_discrete_input_set(0, 1);
	bsp_mb_discrete_input_set(0, 0);
	bsp_mb_discrete_input_set(0, 1);

	// Update input register
	bsp_mb_input_reg_set(0, 1);
	bsp_mb_input_reg_set(1, 2);
	bsp_mb_input_reg_set(2, 3);
	bsp_mb_input_reg_set(3, 4);

	// Update holding register
	bsp_mb_holding_reg_set(0, 5);
	bsp_mb_holding_reg_set(1, 6);
	bsp_mb_holding_reg_set(2, 7);
	bsp_mb_holding_reg_set(3, 8);
```

Test on modbus master [modbus poll](https://www.modbustools.com/download.html)

![](docs/image/test_modbus.png)


## Modbus register and application usage

Modbus and application work via the register, modbus read/write value to register then application write the value to ouput or update value/status from peripheral

![](docs/image/modbus_arch.png)

## Tools

1. [qModbus Master](https://sourceforge.net/projects/qmodmaster/), Or [Tools/qModMaster-Win64-exe-0.5.3-beta.zip](tools/qModMaster-Win64-exe-0.5.3-beta.zip)

2. [Modbus poll](https://www.modbustools.com/download.html)
