/*
 * mb_log.h
 *
 *  Created on: Jun 11, 2022
 *      Author: phatn
 */

#ifndef MB_LOG_H_
#define MB_LOG_H_

#include "mb_config.h"

#ifdef MB_DEBUG
//#define MB_LOG
#endif

#ifdef MB_LOG
#include "SEGGER_RTT.h"
#define mb_log_init()		SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_SKIP)
#define mb_log(_c, ...)		SEGGER_RTT_printf(0, _c, ##__VA_ARGS__);
#else
#define mb_log_init()
#define mb_log(_c, ...)
#endif

#endif /* MB_LOG_H_ */
