/*
 * mb_data_config.h
 *
 *  Created on: Jun 11, 2022
 *      Author: phatn
 */

#ifndef _MB_DATA_CONFIG_H_
#define _MB_DATA_CONFIG_H_

#define MB_COIL_NUM				2000	// number of coil, @note: multiple of 8, @TODO edit
#define MB_INPUT_NUM			2000	// number of input, @note: multiple of 8, @TODO edit
#define MB_REG_INPUT_NUM		1000	// number of reg input , @TODO edit
#define MB_REG_HOLDING_NUM		1000	// number of reg holding, @TODO edit

#if (MB_COIL_NUM %8)
#error "Error: MB_COIL_NUM value should be multiple of 8"
#endif

#if (MB_COIL_NUM > 0x7D0)	// 2000
#error "Error: MB_COIL_NUM should be in range of [1, 2000]"
#endif

#if (MB_INPUT_NUM % 8)
#error "Error: MB_INPUT_NUM value should be multiple of 8"
#endif

#if (MB_INPUT_NUM > 0x7D0)	// 2000
#error "Error: MB_INPUT_NUM should be in range of [1, 2000]"
#endif

#endif /* _MB_DATA_CONFIG_H_ */
