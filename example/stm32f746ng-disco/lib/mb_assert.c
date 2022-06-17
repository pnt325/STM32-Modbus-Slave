/*
 * mb_assert.c
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#include "mb_assert.h"
#include "mb_stm32_include.h"

void __mb_failure(void)
{
	__disable_irq();
	while(1);
}
