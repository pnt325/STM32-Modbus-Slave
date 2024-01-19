/*
 * fm24w256.c
 *
 *  Created on: Jan 19, 2024
 *      Author: admin
 */

#include <string.h>
#include "fm24w256.h"
#include "main.h"
#include "i2c.h"
#include "dma.h"
#include "crc.h"

#define WP_PORT				GPIOB
#define WP_PIN				3

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_i2c1_tx;

#define FRAM_ADDR				0xA0
#define FRAM_I2C				(&hi2c1)
#define FRAM_MEM_ADDR_MAX		32768	/** 32(KBytes) = 32678(Bytes) */
#define FRAM_WRITE_BUF_SIZE		8		/** Handle 8 requeset at time */
#define FRAM_WRITE_DMA_BUF_SIZE	8		/** Allow to write data each request */

typedef struct {
	volatile uint16_t addr;
	uint8_t data[FRAM_WRITE_DMA_BUF_SIZE];
	volatile int len;
} write_obj_t;

static void write_en(bool en);
static int write_bytes(uint16_t addr, uint8_t *data, int len);
static int read_bytes(uint16_t addr, uint8_t *data, int len);
static bool addr_invalid(uint16_t addr, int data_len);
static int writes_dma(uint16_t addr, uint8_t *data, int len);

static write_obj_t write_objs[FRAM_WRITE_BUF_SIZE];
static volatile bool dma_available = true;
static volatile bool dma_on_write = false;
static write_obj_t *last_obj;

int fm24w256_init(void) {
	return 0; /** Success */
}

int fm24w256_writes(uint16_t addr, uint8_t *data, int len) {
	write_en(true);
	return write_bytes(addr, data, len);
}

int fm24w256_reads(uint16_t addr, uint8_t *data, int len) {
	return read_bytes(addr, data, len);
}

int fm24w256_writes_dma(uint16_t addr, uint8_t *data, int len) {
	if (addr_invalid(addr, len)) {
		return -1;
	}
	if (len > FRAM_WRITE_DMA_BUF_SIZE) {
		return -1;
	}
	return writes_dma(addr, data, len);
}

uint16_t fm24w256_crc(uint8_t *data, int len) {
	// Hardware CRC accelerator
	uint32_t val = HAL_CRC_Calculate(&hcrc, (uint32_t*) data, len);
	return (uint16_t) val ^ 0x000;
}

int fm24w256_example(void) {
//	const char data[] = "hello world";
//	if(fm24w256_writes(0, (uint8_t*)data, strlen(data)))
//	{
//		return;
//	}
//	HAL_Delay(100);
//	char buf[128];
//	memset((void*) buf, 0, sizeof(buf));
//	if (fm24w256_reads(0, (uint8_t*) buf, sizeof(data))) {
//		return -1;
//	}

	char buf1[] = "Test 1";
	char buf2[] = "Test 2";
	char buf3[] = "Test 3";
	char buf4[] = "Test 4";
	char buf5[] = "Test 5";
	char buf6[] = "Test 6";
	char buf7[] = "Test 7";
	char buf8[] = "Test 8";

	if (fm24w256_writes_dma(0, (uint8_t*) buf1, sizeof(buf1))) {
		return -1;
	}
	if (fm24w256_writes_dma(16, (uint8_t*) buf2, sizeof(buf2))) {
		return -1;
	}
	if (fm24w256_writes_dma(32, (uint8_t*) buf3, sizeof(buf3))) {
		return -1;
	}
	if (fm24w256_writes_dma(48, (uint8_t*) buf4, sizeof(buf4))) {
		return -1;
	}
	if (fm24w256_writes_dma(64, (uint8_t*) buf5, sizeof(buf5))) {
		return -1;
	}
	if (fm24w256_writes_dma(80, (uint8_t*) buf6, sizeof(buf6))) {
		return -1;
	}
	if (fm24w256_writes_dma(96, (uint8_t*) buf7, sizeof(buf7))) {
		return -1;
	}
	if (fm24w256_writes_dma(112, (uint8_t*) buf8, sizeof(buf8))) {
		return -1;
	}

	HAL_Delay(1000);
	memset(buf1, 0, sizeof(buf1));
	memset(buf2, 0, sizeof(buf2));
	memset(buf3, 0, sizeof(buf3));
	memset(buf4, 0, sizeof(buf4));
	memset(buf5, 0, sizeof(buf5));
	memset(buf6, 0, sizeof(buf6));
	memset(buf7, 0, sizeof(buf7));
	memset(buf8, 0, sizeof(buf8));
	if (fm24w256_reads(0, (uint8_t*) buf1, sizeof(buf1))) {
		return -1;
	}
	if (fm24w256_reads(16, (uint8_t*) buf2, sizeof(buf2))) {
		return -1;
	}
	if (fm24w256_reads(32, (uint8_t*) buf3, sizeof(buf3))) {
		return -1;
	}
	if (fm24w256_reads(48, (uint8_t*) buf4, sizeof(buf4))) {
		return -1;
	}
	if (fm24w256_reads(64, (uint8_t*) buf5, sizeof(buf5))) {
		return -1;
	}
	if (fm24w256_reads(80, (uint8_t*) buf6, sizeof(buf6))) {
		return -1;
	}
	if (fm24w256_reads(96, (uint8_t*) buf7, sizeof(buf7))) {
		return -1;
	}
	if (fm24w256_reads(112, (uint8_t*) buf8, sizeof(buf8))) {
		return -1;
	}
	return 0;
}

static void write_en(bool en) {
	HAL_GPIO_WritePin(GPIOB, WP_PIN, !en);
}

static int write_bytes(uint16_t addr, uint8_t *data, int len) {
	if (addr_invalid(addr, len)) {
		return -1;
	}
	return HAL_I2C_Mem_Write(FRAM_I2C, FRAM_ADDR, addr, 2, data, len, 500);
}

static int read_bytes(uint16_t addr, uint8_t *data, int len) {
	if (addr_invalid(addr, len)) {
		return -1;
	}
	return HAL_I2C_Mem_Read(FRAM_I2C, FRAM_ADDR, addr, 2, data, len, 500);
}

static bool addr_invalid(uint16_t addr, int data_len) {
	if ((data_len == 0) || ((addr + data_len) >= FRAM_MEM_ADDR_MAX)) {
		return true;
	}
	return false;
}

static void writes_dma_next(void) {
	if (dma_available == false) {
		return;
	}

	if (dma_on_write) {
		return;
	}
	dma_on_write = true;

	__disable_irq();
	/** Free last object */
	if (last_obj) {
		last_obj->len = 0;
	}
	last_obj = NULL;
	for (int i = 0; i < FRAM_WRITE_BUF_SIZE; i++) {
		if (write_objs[i].len) {
			last_obj = &write_objs[i];
			break;
		}
	}
	__enable_irq();

	if (last_obj == NULL) {
		goto func_ret;
	}
	if (HAL_I2C_Mem_Write_DMA(FRAM_I2C, FRAM_ADDR, last_obj->addr, 2,
			last_obj->data, last_obj->len) == HAL_OK) {
		dma_available = false;
	}
	func_ret: dma_on_write = false;
}

static int writes_dma(uint16_t addr, uint8_t *data, int len) {
	__disable_irq();
	write_obj_t *obj = NULL;
	for (int i = 0; i < FRAM_WRITE_BUF_SIZE; i++) {
		if (write_objs[i].len == 0) {
			obj = &write_objs[i];
			break;
		}
	}
	if (obj) {
		obj->len = len;
		obj->addr = addr;
		for (int i = 0; i < len; i++) {
			obj->data[i] = data[i];
		}
	}
	__enable_irq();

	if (obj == NULL) {
		return -1;
	}

	writes_dma_next();
	return 0;
}

static void i2c_callback_handle(void) {
	dma_available = true;
	writes_dma_next();
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c == FRAM_I2C) {
		i2c_callback_handle();
	}
}
