#ifndef _MB_PORT_H_
#define _MB_PORT_H_

#include <stdint.h>
#include <stdio.h>

/**
 * @brief   Start receive uart 
 * @param   uart        Point to uart instance
 * @param   buf         Point to data
 * @param   buf_size    Number of byte can receive
 */
void mb_port_start_recv(void* uart, uint8_t* buf, uint16_t buf_size);

/**
 * @brief   Start send data
 * @param   uart        Point to uart
 * @param   buf         Point to data
 * @param   bug_size    Number of byte
 */
void mb_port_start_send(void* uart, uint8_t* buf, uint16_t buf_size);

/**
 * @brief   Modbus CRC calculate
 * @param   data        Point to data
 * @param   data_len    Number of byte
 */
uint16_t mb_port_crc_calc(uint8_t* data, uint16_t data_len);

 
#endif /*_MB_PORT_H_*/
