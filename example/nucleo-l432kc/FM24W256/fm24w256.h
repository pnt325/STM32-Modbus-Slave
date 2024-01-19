/*
 * fm24w256.h
 *
 *  Created on: Jan 19, 2024
 *      Author: admin
 */

#ifndef FM24W256_H_
#define FM24W256_H_

#include <stdint.h>
#include <stdbool.h>

int fm24w256_init(void);
int fm24w256_writes(uint16_t addr,uint8_t* data, int len);
int fm24w256_reads(uint16_t addr, uint8_t* data, int len);
int fm24w256_writes_dma(uint16_t addr, uint8_t* data, int len);
int fm24w256_example(void);
uint16_t fm24w256_crc(uint8_t* data, int len);

#endif /* FM24W256_H_ */
