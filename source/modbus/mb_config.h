/*
 * mb_config.h
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#ifndef MB_CONFIG_H_
#define MB_CONFIG_H_

/* Number of MODBUS slave instance ============================*/
#define MB_PDU_SIZE				256

/* STM32 timer configure ======================================*/
#define MB_TIMER_32_BIT			0xFFFFFFFF
#define MB_TIMER_16_BIT			0xFFFF

#define MB_TIMER_RESOLUTION		MB_TIMER_16_BIT				// TODO Configure it
#define MB_TIMER_CLOCK_SOURCE	100	// Mhz					// TODO Configure it

/* Debug configure ============================================*/
#define MB_DEBUG

#endif /* MB_CONFIG_H_ */
