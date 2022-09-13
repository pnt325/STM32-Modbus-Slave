/*
 * mb_assert.h
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#ifndef MB_ASSERT_H_
#define MB_ASSERT_H_

#include <stdbool.h>
#include "mb_config.h"

#ifdef MB_DEBUG
#define MB_ASSERT
#endif

#ifdef MB_ASSERT
extern void __mb_failure(void);
#define mb_assert(_v)			(_v)?(void)0:__mb_failure()
#else
#define mb_assert(_v)
#endif

#endif /* MB_ASSERT_H_ */
