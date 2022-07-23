# MODBUS MASTER

## Configure

### 1. Edit [bsp_modbus_master.h](Core/Inc/bsp_modbus_master.h) modbus instance: the configure for 2 master

```c
typedef enum
{
	BSP_MODBUS_1,
	BSP_MODBUS_2,
	BSP_MODBUS_NUM
}bsp_modbus_master_t;
```

### 2. Update UART instance using for each master: [bsp_modbus_master.c](Core/Src/bsp_modbus_master.c)

```c
modbus_master_t mb_master[BSP_MODBUS_NUM];
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef hlpuart1;
```

Assign UART for each instance with instance name
```c
void bsp_modbus_master_init(void)
{
	mb_master[BSP_MODBUS_1].bsp_get_tick = bsp_get_tick;
	mb_master[BSP_MODBUS_1].bsp_uart_start_transmit = bsp_uart_transmit;
	mb_master[BSP_MODBUS_1].tx_complete_req = false;
	mb_master[BSP_MODBUS_1].uart = &huart1;

	mb_master[BSP_MODBUS_2].bsp_get_tick = bsp_get_tick;
	mb_master[BSP_MODBUS_2].bsp_uart_start_transmit = bsp_uart_transmit;
	mb_master[BSP_MODBUS_2].tx_complete_req = false;
	mb_master[BSP_MODBUS_2].uart = &hlpuart1;

  modbus_master_init(&mb_master[BSP_MODBUS_1]);
  modbus_master_init(&mb_master[BSP_MODBUS_2]);
}
```
## Test

Change modbus master instance in [main.c](Core/Src/main.c) and do the test 


```c
static bsp_modbus_master_t modbus_master = BSP_MODBUS_1;
```