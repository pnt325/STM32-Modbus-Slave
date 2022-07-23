/**
 * @file       modbus_master.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-04-09
 * @author     Thuan Le
 * @brief      Driver support Modbus Master
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "modbus_master.h"

/* Private defines ---------------------------------------------------- */
#define MODBUS_STATUS_TRANSACTION_SUCCESS             (0x00)
#define MODBUS_STATUS_INVALID_SLAVE_ID                (0xE0)
#define MODBUS_STATUS_INVALID_FUNCTION                (0xE1)
#define MODBUS_STATUS_EXPIRED_TIMEOUT                 (0xE2)
#define MODBUS_STATUS_INVALID_CRC                     (0xE3)

#define MODBUS_RESPONSE_TIMEOUT                       (2000)



/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
//struct_queue_array modbus_master_tx_queue;
//struct_queue_array modbus_master_rx_queue;
//volatile bool modbus_complete_transmit_req = false;

/* Private variables -------------------------------------------------- */

//static struct
//{
//  uint8_t tx_buffer_queue[MODBUS_MASTER_TX_BUFFER_SIZE];
//  uint8_t rx_buffer_queue[MODBUS_MASTER_RX_BUFFER_SIZE];
//  uint16_t transmit_buffer[MODBUS_MASTER_TX_BUFFER_SIZE]; // Data want to write to slave
//  uint16_t response_buffer[MODBUS_MASTER_RX_BUFFER_SIZE]; // Data response from slave
//  uint8_t adu[128];
//  uint8_t adu_size;
//
//  uint8_t slave_id;
//  uint16_t read_addr;
//  uint16_t read_quantity;
//  uint16_t write_addr;
//  uint16_t write_quantity;
//} modbus_master;

/* Private function prototypes ---------------------------------------- */
static uint8_t modbus_master_execute_transaction(modbus_master_t *modbus, modbus_master_function_t modbus_function);
static void modbus_master_clear_adu(modbus_master_t *modbus);

/* Function definitions ----------------------------------------------- */
void modbus_master_init(modbus_master_t *modbus)
{
	 Queue_Initialize(&modbus->tx_queue, modbus->context.tx_buffer_queue, sizeof(modbus->context.tx_buffer_queue));
	 Queue_Initialize(&modbus->rx_queue, modbus->context.rx_buffer_queue, sizeof(modbus->context.rx_buffer_queue));

	 HAL_UART_Receive_IT(modbus->uart, &modbus->rx_buf, 1);

//  Queue_Initialize(&modbus_master_tx_queue, modbus_master.tx_buffer_queue, sizeof(modbus_master.tx_buffer_queue));
//  Queue_Initialize(&modbus_master_rx_queue, modbus_master.rx_buffer_queue, sizeof(modbus_master.rx_buffer_queue));
}

static void modbus_master_clear_adu(modbus_master_t *modbus)
{
	// TODO should check again to make sure sizeof result correct value
	memset(modbus->context.adu, 0x00, sizeof(modbus->context.adu));
//  memset(modbus_master.adu, 0, sizeof(modbus_master.adu));
}

uint16_t modbus_master_get_response_buffer(modbus_master_t *modbus, uint8_t index)
{
	return modbus->context.response_buffer[index];
//  return modbus_master.response_buffer[index];
}

void modbus_master_clear_response_buffer(modbus_master_t *modbus)
{
	// [x] budfix
	memset(modbus->context.response_buffer, 0x00, sizeof(modbus->context.response_buffer));
//  memset(modbus_master.response_buffer, 0, MODBUS_MASTER_RX_BUFFER_SIZE);
}

void modbus_master_set_transmit_buffer(modbus_master_t *modbus, uint8_t index, uint16_t value)
{
  if (index < MODBUS_MASTER_TX_BUFFER_SIZE)
  {
	  modbus->context.transmit_buffer[index] = value;
//    modbus_master.transmit_buffer[index] = value;
  }
}

void modbus_master_clear_transmit_buffer(modbus_master_t *modbus)
{
	memset(modbus->context.transmit_buffer, 0, sizeof(modbus->context.transmit_buffer));
  // memset(modbus_master.transmit_buffer, 0, MODBUS_MASTER_TX_BUFFER_SIZE);
}

static uint8_t modbus_master_execute_transaction(modbus_master_t *modbus, modbus_master_function_t modbus_function)
{
  uint8_t  i                   = 0;
  uint8_t  quantity            = 0;
  uint16_t crc16               = 0xFFFF;
  uint8_t  byte_left           = 0;
  uint32_t modbus_loop_timeout = 0;
  uint8_t  modbus_status       = MODBUS_STATUS_TRANSACTION_SUCCESS;

  // Setup ADU frame Assemble Modbus Request Application Data Unit
  modbus->context.adu_size = 0;
  modbus->context.adu[modbus->context.adu_size++] = modbus->context.slave_id;
  modbus->context.adu[modbus->context.adu_size++] = modbus_function;

  switch (modbus_function)
  {
  case MODBUS_FUNCTION_READ_COILS:
  case MODBUS_FUNCTION_READ_DISCRETE_INPUTS:
  case MODBUS_FUNCTION_READ_HOLDING_REGISTERS:
  case MODBUS_FUNCTION_READ_INPUT_REGISTERS:
  case MODBUS_FUNCTION_READ_WRITE_MUTIPLE_REGISTERS:

	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.read_addr);
	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.read_addr);
	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.read_quantity);
	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.read_quantity);

		break;
	case MODBUS_FUNCTION_MASK_WRITE_REGISTERS:
	default:
		break;
  }

  switch (modbus_function)
  {
  case MODBUS_FUNCTION_WRITE_SINGLE_COIL:
  case MODBUS_FUNCTION_MASK_WRITE_REGISTERS:
  case MODBUS_FUNCTION_WRITE_MUTIPLE_COILS:
  case MODBUS_FUNCTION_WRITE_SINGLE_REGISTER:
  case MODBUS_FUNCTION_WRITE_MUTIPLE_REGISTERS:
  case MODBUS_FUNCTION_READ_WRITE_MUTIPLE_REGISTERS:

	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.write_addr);
	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.write_addr);

    break;
	case MODBUS_FUNCTION_READ_INPUT_REGISTERS:
	default:
		break;
  }

  switch (modbus_function)
  {
  case MODBUS_FUNCTION_WRITE_SINGLE_COIL:
	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.write_quantity);
	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.write_quantity);
    break;

  case MODBUS_FUNCTION_WRITE_SINGLE_REGISTER:
	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.transmit_buffer[0]);
	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.transmit_buffer[0]);
    break;

  case MODBUS_FUNCTION_WRITE_MUTIPLE_COILS:
	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.write_quantity);
	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.write_quantity);

    if (modbus->context.write_quantity % 8)
      quantity = (modbus->context.write_quantity >> 3) + 1;
    else
      quantity = modbus->context.write_quantity >> 3;

    for (i = 0; i < quantity; i++)
    {
      switch (i % 2)
      {
      case 0:
    	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.transmit_buffer[i >> 1]);
        break;

      case 1:
    	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.transmit_buffer[i >> 1]);
        break;
      }
    }

    break;

  case MODBUS_FUNCTION_WRITE_MUTIPLE_REGISTERS:
  case MODBUS_FUNCTION_READ_WRITE_MUTIPLE_REGISTERS:
    for (i = 0; i < LOW_BYTE(modbus->context.write_quantity); i++)
    {
    	modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.transmit_buffer[i]);
    	modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.transmit_buffer[i]);
    }
    break;

  case MODBUS_FUNCTION_MASK_WRITE_REGISTERS:
	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.transmit_buffer[0]);
	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.transmit_buffer[0]);
	  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(modbus->context.transmit_buffer[1]);
	  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(modbus->context.transmit_buffer[1]);

    break;
  case MODBUS_FUNCTION_READ_INPUT_REGISTERS:
  default:
	  break;
  }

  // CRC calculation {
  crc16 = 0xFFFF;
  for (i = 0; i < modbus->context.adu_size; i++)
    crc16 = util_crc16_update(crc16, modbus->context.adu[i]);

  modbus->context.adu[modbus->context.adu_size++] = LOW_BYTE(crc16);
  modbus->context.adu[modbus->context.adu_size++] = HIGH_BYTE(crc16);
  modbus->context.adu[modbus->context.adu_size] = 0;
  // }
  // End of setup ADU frame ========================================}

  // Queue_MakeNull(&modbus_master_rx_queue);
  Queue_MakeNull(&modbus->rx_queue);
  modbus->tx_complete_req = false;

  for (i = 0; i < modbus->context.adu_size; i++)
  {
    if (Queue_IsFull(&modbus->tx_queue) == 0)
      Queue_EnQueue(&modbus->tx_queue, modbus->context.adu[i]);
  }

  // Start and wait transmit completed
  modbus->bsp_uart_start_transmit(modbus);
  while (modbus->tx_complete_req == false)
    ;

  // Clear Application Data Unit
  modbus_master_clear_adu(modbus);

  modbus_status          = MODBUS_STATUS_TRANSACTION_SUCCESS;
  modbus->context.adu_size = 0;
  modbus_loop_timeout    = modbus->bsp_get_tick();

  while (modbus->context.adu_size < 3)
  {
    if (Queue_IsEmpty(&modbus->rx_queue) == 0)
    	modbus->context.adu[modbus->context.adu_size++] = Queue_DeQueue(&modbus->rx_queue);

    if (modbus->context.adu_size >= 3)
    {
      if (modbus->context.adu[0] != modbus->context.slave_id)
      {
        modbus_status = MODBUS_STATUS_INVALID_SLAVE_ID;
        return modbus_status;
      }

      if ((modbus->context.adu[1] & 0x7F) != modbus_function)
      {
        modbus_status = MODBUS_STATUS_INVALID_FUNCTION;
        return modbus_status;
      }

      if (BIT_READ(modbus->context.adu[1], 7))
      {
        modbus_status = modbus->context.adu[2];
        return modbus_status;
      }
    }

    if ((modbus->bsp_get_tick() - modbus_loop_timeout) > MODBUS_RESPONSE_TIMEOUT && modbus_status == MODBUS_STATUS_TRANSACTION_SUCCESS)
    {
      modbus_status = MODBUS_STATUS_EXPIRED_TIMEOUT;
      return modbus_status;
    }
  }

  if (modbus_status == MODBUS_STATUS_TRANSACTION_SUCCESS)
  {
    switch (modbus->context.adu[1])
    {
    case MODBUS_FUNCTION_READ_COILS:
    case MODBUS_FUNCTION_READ_DISCRETE_INPUTS:
    case MODBUS_FUNCTION_READ_HOLDING_REGISTERS:
    case MODBUS_FUNCTION_READ_INPUT_REGISTERS:
    case MODBUS_FUNCTION_READ_WRITE_MUTIPLE_REGISTERS:
      byte_left = modbus->context.adu[2];
      break;

    case MODBUS_FUNCTION_WRITE_SINGLE_COIL:
    case MODBUS_FUNCTION_WRITE_MUTIPLE_COILS:
    case MODBUS_FUNCTION_WRITE_SINGLE_REGISTER:
    case MODBUS_FUNCTION_WRITE_MUTIPLE_REGISTERS:
      byte_left = 3;
      break;

    case MODBUS_FUNCTION_MASK_WRITE_REGISTERS:
      byte_left = 5;
      break;
    }
  }

  byte_left = byte_left + 2;

  while (byte_left)
  {
    if (Queue_IsEmpty(&modbus->rx_queue) == 0)
    {
    	modbus->context.adu[modbus->context.adu_size++] = Queue_DeQueue(&modbus->rx_queue);
      byte_left--;
    }

    if ((modbus->bsp_get_tick() - modbus_loop_timeout) > MODBUS_RESPONSE_TIMEOUT && modbus_status == MODBUS_STATUS_TRANSACTION_SUCCESS)
    {
      modbus_status = MODBUS_STATUS_EXPIRED_TIMEOUT;
      return modbus_status;
    }
  }

  if (modbus_status == MODBUS_STATUS_TRANSACTION_SUCCESS && byte_left == 0)
  {
    crc16 = 0xFFFF;
    for (i = 0; i < (modbus->context.adu_size - 2); i++)
      crc16 = util_crc16_update(crc16, modbus->context.adu[i]);

    if ((LOW_BYTE(crc16) != modbus->context.adu[modbus->context.adu_size - 2] ||
         HIGH_BYTE(crc16) != modbus->context.adu[modbus->context.adu_size - 1]))
    {
      modbus_status = MODBUS_STATUS_INVALID_CRC;
      return modbus_status;
    }
    else
    {
      switch (modbus->context.adu[1])
      {
      case MODBUS_FUNCTION_READ_COILS:
      case MODBUS_FUNCTION_READ_DISCRETE_INPUTS:
        for (i = 0; i < modbus->context.adu[2] >> 1; i++)
        {
          if (i < MODBUS_MASTER_RX_BUFFER_SIZE)
        	  modbus->context.response_buffer[i] = util_word(modbus->context.adu[(2 * i) + 4], modbus->context.adu[(2 * i) + 3]);
        }

        if (modbus->context.adu[2] % 2)
        {
          if (i < MODBUS_MASTER_RX_BUFFER_SIZE)
        	  modbus->context.response_buffer[i] = util_word(0, modbus->context.adu[(2 * i) + 3]);
        }
        break;
      case MODBUS_FUNCTION_READ_HOLDING_REGISTERS:
      case MODBUS_FUNCTION_READ_INPUT_REGISTERS:
      case MODBUS_FUNCTION_READ_WRITE_MUTIPLE_REGISTERS:
        for (i = 0; i < (modbus->context.adu[2] >> 1); i++)
        {
          if (i < MODBUS_MASTER_RX_BUFFER_SIZE)
        	  modbus->context.response_buffer[i] = util_word(modbus->context.adu[2 * i + 3], modbus->context.adu[2 * i + 4]);
        }
        break;
      }
    }
  }

  if ((modbus->bsp_get_tick() - modbus_loop_timeout) > MODBUS_RESPONSE_TIMEOUT && modbus_status == MODBUS_STATUS_TRANSACTION_SUCCESS)
    modbus_status = MODBUS_STATUS_EXPIRED_TIMEOUT;

  return modbus_status;
}

uint8_t modbus_master_read_coils(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
	modbus->context.slave_id      = slave_id;
	modbus->context.read_addr     = read_addr;
	modbus->context.read_quantity = size;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_READ_COILS);
}

uint8_t modbus_master_read_discrete_input(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
	modbus->context.slave_id      = slave_id;
	modbus->context.read_addr     = read_addr;
	modbus->context.read_quantity = size;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_READ_DISCRETE_INPUTS);
}

uint8_t modbus_master_read_holding_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
	modbus->context.slave_id      = slave_id;
	modbus->context.read_addr     = read_addr;
	modbus->context.read_quantity = size;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_READ_HOLDING_REGISTERS);
}

uint8_t modbus_master_read_input_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t size)
{
	modbus->context.slave_id      = slave_id;
	modbus->context.read_addr     = read_addr;
	modbus->context.read_quantity = size;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_READ_INPUT_REGISTERS);
}

uint8_t modbus_master_write_single_coil(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint8_t state)
{
	modbus->context.slave_id   = slave_id;
	modbus->context.write_addr = write_addr;
  
  if (state)
	  modbus->context.write_quantity = 0xff00;
  else
	  modbus->context.write_quantity = 0x0000;
  
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_WRITE_SINGLE_COIL);
}

uint8_t modbus_master_write_single_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t value)
{
	modbus->context.slave_id       = slave_id;
	modbus->context.write_addr     = write_addr;
	modbus->context.write_quantity = 0;

	modbus->context.transmit_buffer[0] = value;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_WRITE_SINGLE_REGISTER);
}

uint8_t modbus_master_write_mutiple_coils(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t size)
{
	modbus->context.slave_id       = slave_id;
	modbus->context.write_addr     = write_addr;
	modbus->context.write_quantity = size;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_WRITE_MUTIPLE_COILS);
}

uint8_t modbus_master_write_mutiple_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t size)
{
	modbus->context.slave_id       = slave_id;
	modbus->context.write_addr     = write_addr;
	modbus->context.write_quantity = size;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_WRITE_MUTIPLE_REGISTERS);
}

uint8_t modbus_master_mask_write_register(modbus_master_t *modbus, uint8_t slave_id, uint16_t write_addr, uint16_t and_mask, uint16_t or_mask)
{
	modbus->context.slave_id   = slave_id;
	modbus->context.write_addr = write_addr;

	modbus->context.transmit_buffer[0] = and_mask;
	modbus->context.transmit_buffer[1] = or_mask;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_MASK_WRITE_REGISTERS);
}

uint8_t modbus_master_read_mutiple_registers(modbus_master_t *modbus, uint8_t slave_id, uint16_t read_addr, uint16_t read_size,
                                            uint16_t write_addr, uint16_t write_size)
{
	modbus->context.slave_id       = slave_id;
	modbus->context.read_addr      = read_addr;
	modbus->context.read_quantity  = read_size;
	modbus->context.write_addr     = write_addr;
	modbus->context.write_quantity = write_size;
  return modbus_master_execute_transaction(modbus, MODBUS_FUNCTION_READ_WRITE_MUTIPLE_REGISTERS);
}

void modbus_master_rx_irq(modbus_master_t* master)
{
	if(master == NULL)
	{
		// NOTE Show error
		return;
	}

	// TODO toggle pin
	HAL_UART_Receive_IT(master->uart, &master->rx_buf, 1);
	if(Queue_IsFull(&master->rx_queue) == 0)
	{
		Queue_EnQueue(&master->rx_queue, master->rx_buf);
	}
}

void modbus_master_tx_irq(modbus_master_t* master)
{
	if(master == NULL)
	{
		// NOTE Show error
		return;
	}

	if(Queue_IsEmpty(&master->tx_queue) == 1)
	{
		master->tx_complete_req = 1;
	}
	else
	{
		master->tx_buf = Queue_DeQueue(&master->tx_queue);
		HAL_UART_Transmit_IT(master->uart, &master->tx_buf, 1);
	}



}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */