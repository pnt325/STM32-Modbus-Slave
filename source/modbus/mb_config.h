/*
 * mb_config.h
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#ifndef MB_CONFIG_H_
#define MB_CONFIG_H_

/* Number of MODBUS slave instance ============================*/
#define MB_NUM_OF_INSTANCE		1
#define MB_PDU_SIZE				256

/* STM32 timer configure ======================================*/
#define MB_TIMER_32_BIT			0xFFFFFFFF
#define MB_TIMER_16_BIT			0xFFFF

#define MB_TIMER_RESOLUTION		MB_TIMER_16_BIT				// TODO Configure it
#define MB_TIMER_CLOCK_SOURCE	100	// Mhz					// TODO Configure it

/* Debug configure ============================================*/
#define MB_DEBUG

//#ifdef MB_DEBUG
//#define MB_ASSERT
//#define MB_LOG
//#endif
//
//#ifdef MB_ASSERT
//extern void __mb_failure(void);
//#define mb_assert(_v)			(_v)?(void)0:__mb_failure()
//#else
//#define mb_assert(_v)
//#endif

//#ifdef MB_LOG
//#include "SEGGER_RTT.h"
//#define mb_log_init()		SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP)
//#define mb_log(_c, ...)		SEGGER_RTT_printf(0, _c, ##__VA_ARGS__);
//#else
//#define mb_log_init()
//#define mb_log()
//#endif

#endif /* MB_CONFIG_H_ */
