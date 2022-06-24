/*
 * mb_slave.c
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#include <string.h>
#include <stdio.h>

#include "mb_slave.h"
#include "mb_config.h"
#include "mb_assert.h"
#include "mb_log.h"
#include "mb_defs.h"
#include "mb_crc.h"

/* macro ======================================================*/
#define UART_TX_BUF_SIZE		384

/* type =======================================================*/
struct tx_buf_s{
	uint16_t head;
	uint16_t tail;
	uint8_t  data[UART_TX_BUF_SIZE];
};

/* variable ===================================================*/
 const uint8_t mb_support_fc[] = MB_FC_SUPORT_DEFAULT;

 // UART TX
 static volatile uint16_t tx_len;
 static struct tx_buf_s   tx_buf;


/* private function ===========================================*/
static uint32_t get_t35(uint32_t speed);
static void     set_timer_period(mb_slave_t* mb, uint32_t speed);
static uint8_t  valid_request(mb_slave_t* mb, mb_pdu_t* pdu);
static uint8_t  execute_func(mb_slave_t* mb, mb_pdu_t* pdu);
static void     build_exc(mb_slave_t* mb, mb_pdu_t* pdu, uint8_t code);
static void     set_tx(mb_slave_t* mb, mb_pdu_t* pdu);
static void     start_transmit(mb_slave_t* mb);

static uint8_t fc_read_coil(mb_slave_t* mb, mb_pdu_t* pdu);
static uint8_t fc_read_input(mb_slave_t* mb, mb_pdu_t* pdu);
static uint8_t fc_read_reg_input(mb_slave_t* mb, mb_pdu_t* pdu);
static uint8_t fc_read_reg_hodling(mb_slave_t* mb, mb_pdu_t* pdu);
static uint8_t fc_write_single_coil(mb_slave_t* mb, mb_pdu_t* pdu);
static uint8_t fc_write_single_reg(mb_slave_t* mb, mb_pdu_t* pdu);
static uint8_t fc_write_multi_coil(mb_slave_t* mb, mb_pdu_t* pdu);
static uint8_t fc_write_multi_reg(mb_slave_t* mb, mb_pdu_t* pdu);

mb_return_t mb_slave_init(mb_slave_t* mb, uint8_t sl_addr, uint32_t speed, uint32_t timer_clk_mhz)
{
	mb_assert(mb);
	mb_assert(mb->uart);
	mb_assert(mb->timer);

	mb_log_init();
	mb_log("MODBUS init\n");
	mb_log("Speed: %d\n", speed);

	// Check address rule:
	// MODBUS address should in range from 1 to 247
	// NOTE: Check section "2.2 MODBUS Addressing rules" on "Modbus_over_serial_line_V1_02.pdf"
	if(sl_addr < 1 || sl_addr > 247)
	{
		mb_log("MODBUS error: address invalid: %d\n", sl_addr);
		return MB_FAILURE;
	}

	ring_buffer_init(&mb->uart_buf);
	mb_buffer_init(&mb->buf);
	mb_data_init(&mb->data);
	mb->slave_addr = sl_addr;

	// Timer configure
	__HAL_TIM_CLEAR_IT(mb->timer, TIM_IT_UPDATE);						// Clear IRQ pending
	__HAL_TIM_SET_PRESCALER(mb->timer, (timer_clk_mhz - 1));	// Set timer prescaler
	set_timer_period(mb, speed);

	mb->is_init = true;

	tx_buf.tail = 0;
	tx_buf.head = 0;
	tx_len = 0;

	// Start receive UART
	HAL_UART_Receive_IT(mb->uart, &mb->uart_rx, 1);

	return MB_SUCCESS;
}

mb_return_t mb_slave_deinit(mb_slave_t* mb)
{
	mb_assert(mb);
	if (mb->is_init) {
		mb_log("MODBUS deinit\n");
		mb->is_init = false;

		// Stop timer
		HAL_TIM_Base_Stop_IT(mb->timer);

		// Stop UART
		HAL_UART_AbortReceive_IT(mb->uart);
		HAL_UART_AbortTransmit_IT(mb->uart);

		// Clear buffer
		mb->buf.flush(&mb->buf);
		mb->uart_buf.flush(&mb->uart_buf);

		// Reset transmit buffer
		tx_buf.tail = 0;
		tx_buf.head = 0;
		tx_len = 0;
	}

	return MB_SUCCESS;
}

void mb_slave_handle(mb_slave_t *mb) {
	mb_assert(mb);

	// Reject handle if MODBUS is not initialize
	if(mb->is_init == false){
		return;
	}

	// Handle received data
	if (mb->buf.available(&mb->buf) == 0) {
		return;
	}

	// Check frame PDU data size
	mb_pdu_t* pdu = mb->buf.get_data(&mb->buf);
	if(pdu->len < 8){
		mb_log("MODBUS error: bad frame, len = %d", pdu->len);
		mb->buf.commit_get(&mb->buf);
		return;
	}

	// Slave ID
	if(pdu->data[MB_PDU_ID] != mb->slave_addr){
		return;
	}

#ifdef MB_LOG
	mb_log("Request: ");
	for(uint8_t i = 0; i < pdu->len; i++)
	{
		mb_log("%02x ", pdu->data[i]);
	}
	mb_log("\n");
	mb_log("Func code: %d\n", pdu->data[MB_PDU_FUNC]);
	mb_log("Address  : %d\n", (uint16_t)((uint16_t)pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO]));
#endif

	// Verify CRC
	uint16_t crc = (pdu->data[pdu->len - 2] << 8) | pdu->data[pdu->len - 1];
	if(crc != mb_crc_calc(pdu->data, pdu->len - 2))
	{
		mb_log("MODBUS error: CRC invalid\n");
		return;
	}

	// Handle request
	uint8_t err_code = valid_request(mb, pdu);
	if (err_code) {
		build_exc(mb, pdu, err_code);
	} else {
		err_code = execute_func(mb, pdu);
		if (err_code)
			build_exc(mb, pdu, err_code);
	}

	// Response data
	crc = mb_crc_calc(pdu->data, pdu->len - 2);
	pdu->data[pdu->len - 2] = (uint8_t) (crc >> 8);
	pdu->data[pdu->len - 1] = (uint8_t) (crc & 0x00FF);
	set_tx(mb, pdu);

	// Commit processed data
	mb->buf.commit_get(&mb->buf);
}

void _mb_slave_tx_irq(mb_slave_t* mb)
{
	mb_assert(mb);
	tx_buf.tail = (tx_buf.tail + tx_len) % UART_TX_BUF_SIZE;
	start_transmit(mb);
}

void _mb_slave_rx_irq(mb_slave_t* mb)
{
	mb->uart_buf.add(&mb->uart_buf, mb->uart_rx);

	// Restart timer
	__HAL_TIM_SET_COUNTER(mb->timer, 0);
	HAL_TIM_Base_Start_IT(mb->timer);
	HAL_UART_Receive_IT(mb->uart, &mb->uart_rx, 1);
}

void _mb_slave_timer_irq(mb_slave_t* mb)
{
	// Stop receive UART
	HAL_UART_AbortReceive_IT(mb->uart);
	HAL_TIM_Base_Stop_IT(mb->timer);

	// Copy data from buffer to MODBUS packet
	if(mb->uart_buf.overflow)
	{
		mb->uart_buf.flush(&mb->uart_buf);
	}
	else
	{
		mb_pdu_t *pdu = mb->buf.next(&mb->buf);
		pdu->len = MB_PDU_SIZE;
		mb->uart_buf.get_data(&mb->uart_buf, pdu->data, &pdu->len);
		mb->buf.commit_next(&mb->buf);
	}

	// Start receive UART
	HAL_UART_Receive_IT(mb->uart, &mb->uart_rx, 1);
}

static uint32_t get_t35(uint32_t speed) {
	mb_assert(speed);

	float f_speed = (1000000.0f / ((float) speed / 8.0f));
	f_speed = f_speed * 3.5f;

	mb_log("Get T35: speed = %u, T35 = %u (us)\n", speed, (uint32_t)f_speed);
	return (uint32_t) (f_speed + 1);
}

/**
 * @brief Set timer period of 3.5 char transmit time of UART speed
 * @param speed speed of UART
 */
static void set_timer_period(mb_slave_t* mb ,uint32_t speed)
{
	uint32_t t35 = get_t35(speed);
	__HAL_TIM_SET_AUTORELOAD(mb->timer, t35 - 1);
}

static uint8_t valid_request(mb_slave_t* mb,mb_pdu_t* pdu)
{
	// Supported function
	uint8_t i;
	for(i = 0; i < sizeof(mb_support_fc);i++)
	{
		if(pdu->data[MB_PDU_FUNC] == mb_support_fc[i])
		break;
	}

	if (i >= sizeof(mb_support_fc)) {
		mb_log("MB function not support\n");
		return MB_EXC_FUNC;
	}

	uint16_t addr;	// start address
	uint16_t nreg;	// number of reg

	addr = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	nreg = pdu->data[MB_PDU_QTY_HI] << 8  | pdu->data[MB_PDU_QTY_LO];

	switch(pdu->data[MB_PDU_FUNC])
	{
	case MB_FC_READ_COIL:
		if (!((nreg >= 1) && (nreg <= mb->data.coil.nbit)))
			return MB_EXC_ADDR_RANGE;
		if(!((addr < mb->data.coil.nbit) && ((addr + nreg) <= mb->data.coil.nbit)))
			return MB_EXC_REG_QTY;
		break;
	case MB_FC_READ_DISCRETE_INPUT:
		if (!((nreg >= 1) && (nreg <= mb->data.input.nbit)))
			return MB_EXC_ADDR_RANGE;
		if(!((addr < mb->data.input.nbit) && ((addr + nreg) <= mb->data.input.nbit)))
			return MB_EXC_REG_QTY;
		break;
	case MB_FC_READ_INPUT_REG:
		if (mb->data.reg_input.nreg > 0x7D) {
			if (!(nreg >= 1 && nreg <= 0x7D))
				return MB_EXC_ADDR_RANGE;
		} else {
			if (!(nreg >= 1 && nreg <= mb->data.reg_input.nreg))
				return MB_EXC_ADDR_RANGE;
		}
		if(!((addr < mb->data.reg_input.nreg) && ((addr + nreg ) <= mb->data.reg_input.nreg)))
			return MB_EXC_REG_QTY;
		break;
	case MB_FC_READ_HOLDING_REG:
		if (mb->data.reg_holding.nreg > 0x7D) {
			if (!(nreg >= 1 && nreg <= 0x7D))
				return MB_EXC_ADDR_RANGE;
		} else {
			if (!((nreg >= 1) && (nreg <= mb->data.reg_holding.nreg)))
				return MB_EXC_ADDR_RANGE;
		}
		if(!((addr < mb->data.reg_holding.nreg) && ((addr + nreg ) <= mb->data.reg_holding.nreg)))
			return MB_EXC_REG_QTY;
		break;
	case MB_FC_WRITE_MULTI_COIL:
	{
		// Get number of byte
		uint8_t nbyte = nreg / 8;
		if(nreg % 8)
			nbyte += 1;

		if(!((nreg >= 1) && (nreg <= mb->data.coil.nbit) && (nbyte == pdu->data[MB_PDU_CNT])))
			return MB_EXC_REG_QTY;
		if(!((addr < mb->data.coil.nbit) && ((addr + nreg) <= mb->data.coil.nbit)))
			return MB_EXC_ADDR_RANGE;
		break;
	}
	case MB_FC_WRITE_SINGLE_COIL:
		if(!((nreg == 0x0000) || (nreg == 0xFF00)))
			return MB_EXC_REG_QTY;
		if(!(addr < mb->data.coil.nbit))
			return MB_EXC_ADDR_RANGE;
		break;
	case MB_FC_WRITE_MULTI_REG:
		if(mb->data.reg_holding.nreg < 0x7B) {
			if (!((nreg >= 1) && (nreg <= mb->data.reg_holding.nreg) && (pdu->data[MB_PDU_CNT] == nreg * 2)))
				return MB_EXC_REG_QTY;
		} else {
			if (!((nreg >= 1) && (nreg <= 0x7B) && (pdu->data[MB_PDU_CNT] == nreg * 2)))
				return MB_EXC_REG_QTY;
		}
		if(!((addr < mb->data.reg_holding.nreg) && ((addr + nreg) <= mb->data.reg_holding.nreg)))
			return MB_EXC_ADDR_RANGE;
		break;
	case MB_FC_WRITE_SINGLE_REG:
		if(!(addr <= mb->data.reg_holding.nreg))
			return MB_EXC_ADDR_RANGE;
		break;
	}

	return 0;
}

static uint8_t execute_func(mb_slave_t* mb, mb_pdu_t* pdu)
{
	switch (pdu->data[MB_PDU_FUNC]) {
	case MB_FC_READ_COIL:
		return fc_read_coil(mb, pdu);
	case MB_FC_READ_DISCRETE_INPUT:
		return fc_read_input(mb, pdu);
	case MB_FC_READ_HOLDING_REG:
		return fc_read_reg_hodling(mb, pdu);
	case MB_FC_READ_INPUT_REG:
		return fc_read_reg_input(mb, pdu);
	case MB_FC_WRITE_SINGLE_COIL:
		return fc_write_single_coil(mb, pdu);
	case MB_FC_WRITE_SINGLE_REG:
		return fc_write_single_reg(mb, pdu);
	case MB_FC_WRITE_MULTI_COIL:
		return fc_write_multi_coil(mb, pdu);
	case MB_FC_WRITE_MULTI_REG:
		return fc_write_multi_reg(mb, pdu);
	default:
		break;
	}
	return 0;
}

/**
 * @brief Build exception code.
 */
static void build_exc(mb_slave_t* mb, mb_pdu_t* pdu, uint8_t code)
{
	/**
	 * Response
	 * +----+----+----------+-----+
	 * | ID | FC | EXC_CODE | CRC |
	 * +----+----+----------+-----+
	 * | 1  | 1  |   1      |  2  |
	 * +----+----+----------+-----+
	 * len = 5
	 */

	pdu->data[MB_PDU_FUNC] = pdu->data[MB_PDU_FUNC] + 0x80;
	pdu->data[2] = code;
	pdu->len = 5;

	mb_log("EXC code: %d\n", pdu->data[MB_PDU_FUNC]);
}

static void set_tx(mb_slave_t* mb, mb_pdu_t* pdu)
{
#ifdef MB_LOG
	mb_log("Response: ");
	for(uint16_t i = 0; i < pdu->len; i++)
	{
		mb_log("%02x ", pdu->data[i]);
	}
	mb_log("\n");
#endif

	// Copy data to tx buffer
	for (uint16_t i = 0; i < pdu->len; i++) {
		tx_buf.data[tx_buf.head] = pdu->data[i];
		tx_buf.head = (tx_buf.head + 1) % UART_TX_BUF_SIZE;
		mb_assert(tx_buf.head != tx_buf.tail);
	}

	start_transmit(mb);
}

static void start_transmit(mb_slave_t* mb) {
	if (tx_buf.tail == tx_buf.head)
		return;

	if (tx_buf.tail < tx_buf.head) {
		tx_len = tx_buf.head - tx_buf.tail;
	} else {
		tx_len = UART_TX_BUF_SIZE - tx_buf.tail;
	}

	HAL_UART_Transmit_IT(mb->uart, &tx_buf.data[tx_buf.tail], tx_len);
}

static uint8_t fc_read_coil(mb_slave_t* mb, mb_pdu_t* pdu)
{
	/**
	 * +----+----+------+-----+-----+
	 * | ID | FC | ADDR | QTY | CRC |
	 * +----+----+------+-----+-----+
	 * | 1  | 1  |   2  |  2  |  2  |
	 * +----+----+------+-----+-----+
	 * len = 8
	 */

	if(pdu->len < 8)
		return MB_EXC_EXECUTE;

	uint16_t addr = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	uint16_t qty  = pdu->data[MB_PDU_QTY_HI] << 8 | pdu->data[MB_PDU_QTY_LO];

	/**
	 * Response data
	 * +----+----+-----+------+-----+
	 * | ID | FC | CNT | DATA | CRC |
	 * +----+----+-----+------+-----+
	 * | 1  |  1 |  1  |  n   |  2  |
	 * +----+----+-----+------+-----+
	 */

	pdu->data[2] = qty / 8;
	if(qty % 8)
		pdu->data[2] += 1;

	uint8_t* data = &pdu->data[3];
	memset(data, 0x00, pdu->data[2]);

	for(uint16_t i = 0; i < qty; i++)
	{
		uint8_t ibyte = i / 8;
		uint8_t ibit  = i % 8;
		uint8_t val   = 1 << ibit;

		if(mb->data.coil.get(&mb->data.coil, addr + i))
			data[ibyte] = data[ibyte] | val;
		else
			data[ibyte] = data[ibyte] & (~val);
	}

	pdu->len = pdu->data[2] + 5;	// include CRC
	return 0;
}

static uint8_t fc_read_input(mb_slave_t* mb, mb_pdu_t* pdu)
{
	/**
	 * +----+----+------+-----+-----+
	 * | ID | FC | ADDR | QTY | CRC |
	 * +----+----+------+-----+-----+
	 * | 1  | 1  |   2  |  2  |  2  |
	 * +----+----+------+-----+-----+
	 * len = 8
	 */

	if(pdu->len < 8)
		return MB_EXC_EXECUTE;

	uint16_t addr = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	uint16_t qty  = pdu->data[MB_PDU_QTY_HI] << 8 | pdu->data[MB_PDU_QTY_LO];

	/**
	 * Response data
	 * +----+----+-----+------+-----+
	 * | ID | FC | CNT | DATA | CRC |
	 * +----+----+-----+------+-----+
	 * | 1  |  1 |  1  |  n   |  2  |
	 * +----+----+-----+------+-----+
	 */

	pdu->data[2] = qty / 8;
	if(qty % 8)
		pdu->data[2] += 1;

	uint8_t* data = &pdu->data[3];
	memset(data, 0x00, pdu->data[2]);

	for(uint16_t i = 0; i < qty; i++)
	{
		uint8_t ibyte = i / 8;
		uint8_t ibit  = i % 8;
		uint8_t val   = 1 << ibit;

		if(mb->data.coil.get(&mb->data.input, addr + i))
			data[ibyte] = data[ibyte] | val;
		else
			data[ibyte] = data[ibyte] & (~val);
	}

	pdu->len = pdu->data[2] + 5;	// include CRC
	return 0;
}

static uint8_t fc_read_reg_input(mb_slave_t* mb, mb_pdu_t* pdu)
{
	/**
	 * +----+----+------+-----+-----+
	 * | ID | FC | ADDR | QTY | CRC |
	 * +----+----+------+-----+-----+
	 * | 1  | 1  |   2  |  2  |  2  |
	 * +----+----+------+-----+-----+
	 * len = 8
	 */

	if(pdu->len < 8)
		return MB_EXC_EXECUTE;

	uint16_t addr = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	uint16_t qty  = pdu->data[MB_PDU_QTY_HI] << 8 | pdu->data[MB_PDU_QTY_LO];

	/**
	 * Response data
	 * +----+----+-----+------+-----+
	 * | ID | FC | CNT | DATA | CRC |
	 * +----+----+-----+------+-----+
	 * | 1  |  1 |  1  |  n   |  2  |
	 * +----+----+-----+------+-----+
	 */

	pdu->data[2] = qty * 2;
	uint8_t* data = &pdu->data[3];
	memset(data, 0x00, pdu->data[2]);

	uint16_t data_index = 0;
	for(uint8_t i = 0; i < qty; i++)
	{
		uint16_t value     = mb->data.reg_input.get(&mb->data.reg_input, addr + i);
		data[data_index++] = value >> 8;
		data[data_index++] = (uint8_t)value;
	}

	pdu->len = pdu->data[2] + 5;	// include CRC
	return 0;
}

static uint8_t fc_read_reg_hodling(mb_slave_t* mb, mb_pdu_t* pdu)
{
	/**
	 * +----+----+------+-----+-----+
	 * | ID | FC | ADDR | QTY | CRC |
	 * +----+----+------+-----+-----+
	 * | 1  | 1  |   2  |  2  |  2  |
	 * +----+----+------+-----+-----+
	 * len = 8
	 */

	if(pdu->len < 8)
		return MB_EXC_EXECUTE;

	uint16_t addr = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	uint16_t qty  = pdu->data[MB_PDU_QTY_HI] << 8 | pdu->data[MB_PDU_QTY_LO];

	/**
	 * Response data
	 * +----+----+-----+------+-----+
	 * | ID | FC | CNT | DATA | CRC |
	 * +----+----+-----+------+-----+
	 * | 1  |  1 |  1  |  n   |  2  |
	 * +----+----+-----+------+-----+
	 */

	uint16_t idata = 0;
	uint8_t* data  = &pdu->data[3];

	pdu->data[2]  = qty * 2;
	memset(data, 0x00, pdu->data[2]);

	for(uint8_t i = 0; i < qty; i++)
	{
		uint16_t value = mb->data.reg_holding.get(&mb->data.reg_holding, addr + i);
		data[idata++] = (uint8_t)(value >> 8);
		data[idata++] = (uint8_t)(value);
	}

	pdu->len = pdu->data[2] + 5;	// include CRC
	return 0;
}

static uint8_t fc_write_single_coil(mb_slave_t* mb, mb_pdu_t* pdu)
{
	/**
	 * +----+----+------+-------+-----+
	 * | ID | FC | ADDR | VALUE | CRC |
	 * +----+----+------+-------+-----+
	 * | 1  | 1  |   2  |  2    |  2  |
	 * +----+----+------+-------+-----+
	 * len = 8
	 */

	if(pdu->len < 8)
		return MB_EXC_EXECUTE;

	uint16_t addr  = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	uint16_t value = pdu->data[MB_PDU_QTY_HI]  << 8 | pdu->data[MB_PDU_QTY_LO];

	/**
	 * Response
	 * +----+----+------+-------+-----+
	 * | ID | FC | ADDR | VALUE | CRC |
	 * +----+----+------+-------+-----+
	 * | 1  | 1  |   2  |  2    |  2  |
	 * +----+----+------+-------+-----+
	 * len = 8
	 */

	if (value == 0x00000)
		mb->data.coil.set(&mb->data.coil, addr, 0);
	else
		mb->data.coil.set(&mb->data.coil, addr, 1);

	return 0;
}

static uint8_t fc_write_single_reg(mb_slave_t* mb, mb_pdu_t* pdu)
{
	/**
	 * +----+----+------+-------+-----+
	 * | ID | FC | ADDR | VALUE | CRC |
	 * +----+----+------+-------+-----+
	 * | 1  | 1  |   2  |  2    |  2  |
	 * +----+----+------+-------+-----+
	 * len = 8
	 */

	if(pdu->len < 8)
		return MB_EXC_EXECUTE;

	uint16_t addr  = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	uint16_t value = pdu->data[MB_PDU_QTY_HI]  << 8 | pdu->data[MB_PDU_QTY_LO];

	/**
	 * Response
	 * +----+----+------+-------+-----+
	 * | ID | FC | ADDR | VALUE | CRC |
	 * +----+----+------+-------+-----+
	 * | 1  | 1  |   2  |  2    |  2  |
	 * +----+----+------+-------+-----+
	 * len = 8
	 */

	mb->data.reg_holding.set(&mb->data.reg_holding, addr, value);

	return 0;
}

static uint8_t fc_write_multi_coil(mb_slave_t* mb, mb_pdu_t* pdu)
{
	/**
	 * +----+----+------+-----+-----+------+-----+
	 * | ID | FC | ADDR | QTY | CNT | DATA | CRC |
	 * +----+----+------+-----+-----+------+-----+
	 * | 1  | 1  |   2  |  2  |  1  |   N  |  2  |
	 * +----+----+------+-----+-----+------+-----+
	 * len_min = 10
	 */

	if(pdu->len < 10)
		return MB_EXC_EXECUTE;

	uint16_t addr  = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	uint16_t qty   = pdu->data[MB_PDU_QTY_HI]  << 8 | pdu->data[MB_PDU_QTY_LO];
	uint8_t  b_cnt = pdu->data[MB_PDU_CNT];

	uint8_t _cnt = qty / 8;
	if(qty % 8)
		_cnt += 1;

	if (((b_cnt + 9) != pdu->len) || (_cnt != b_cnt))
		return MB_EXC_EXECUTE;

	uint8_t* data = &pdu->data[7];
	for(uint8_t i  = 0; i < qty; i++)
	{
		uint8_t ibyte = i / 8;
		uint8_t ibit  = i % 8;

		uint8_t status = (data[ibyte] >> ibit) & 0x01;
		mb->data.coil.set(&mb->data.coil, addr + i, status);
	}

	/**
	 * Response
	 * +----+----+------+-----+-----+
	 * | ID | FC | ADDR | QTY | CRC |
	 * +----+----+------+-----+-----+
	 * | 1  | 1  |   2  |  2  |  2  |
	 * +----+----+------+-----+-----+
	 * len_min = 8
	 */

	pdu->len = 8;	// include CRC

	return 0;
}

static uint8_t fc_write_multi_reg(mb_slave_t* mb, mb_pdu_t* pdu)
{
	/**
	 * +----+----+------+-----+-----+------+-----+
	 * | ID | FC | ADDR | QTY | CNT | DATA | CRC |
	 * +----+----+------+-----+-----+------+-----+
	 * | 1  | 1  |   2  |  2  |  1  |   N  |  2  |
	 * +----+----+------+-----+-----+------+-----+
	 * len_min = 11
	 */

	if(pdu->len < 11)
		return MB_EXC_EXECUTE;

	uint16_t addr  = pdu->data[MB_PDU_ADDR_HI] << 8 | pdu->data[MB_PDU_ADDR_LO];
	uint16_t qty   = pdu->data[MB_PDU_QTY_HI]  << 8 | pdu->data[MB_PDU_QTY_LO];
	uint8_t  b_cnt = pdu->data[MB_PDU_CNT];

	if ((qty*2 != b_cnt) || ((b_cnt + 9) != pdu->len))
		return MB_EXC_EXECUTE;

	uint8_t* data = &pdu->data[7];
	uint16_t data_index = 0;
	for(uint8_t i = 0; i < qty; i++)
	{
		uint8_t hi = data[data_index++];
		uint8_t lo = data[data_index++];
		uint16_t value = hi << 8 | lo;
		mb->data.reg_holding.set(&mb->data.reg_holding, addr + i, value);
	}

	/**
	 * Response
	 * +----+----+------+-----+-----+
	 * | ID | FC | ADDR | QTY | CRC |
	 * +----+----+------+-----+-----+
	 * | 1  | 1  |   2  |  2  |  2  |
	 * +----+----+------+-----+-----+
	 * len_min = 8
	 */

	pdu->len = 8;	// include CRC

	return 0;
}

