/*
 * mb_assert.c
 *
 *  Created on: Jun 8, 2022
 *      Author: phatn
 */

#include "stm32f746xx.h"

void __mb_failure(void)
{
	__disable_irq();
	while(1);
}
