/*
 * modbus_slave_example.c
 *
 *  Created on: Jul 21, 2022
 *      Author: phatn
 */

#include "../../lib/bsp_mb_slave.h"
#include "../../lib/mb_log.h"
#include "main.h"

static int64_t tot1 = 1759687;	// Init value to test
static uint32_t tot1_period = 0;

void modbus_slave_example_init(void)
{
	bsp_mb_slave_init();

	// Update coil status
	bsp_mb_coil_set(0, 1);
	bsp_mb_coil_set(1, 0);
	bsp_mb_coil_set(2, 1);
	bsp_mb_coil_set(3, 0);

	// Update input register
	bsp_mb_discrete_input_set(0, 0);
	bsp_mb_discrete_input_set(1, 1);
	bsp_mb_discrete_input_set(2, 0);
	bsp_mb_discrete_input_set(3, 1);

	// Update input register
//	bsp_mb_input_reg_set(0, 1);
//	bsp_mb_input_reg_set(1, 2);
//	bsp_mb_input_reg_set(2, 3);
//	bsp_mb_input_reg_set(3, 4);

	// Update holding register
	bsp_mb_holding_reg_set(0, 5);
	bsp_mb_holding_reg_set(1, 6);
	bsp_mb_holding_reg_set(2, 7);
	bsp_mb_holding_reg_set(3, 8);

	tot1_period = HAL_GetTick();
}

void modbus_slave_example_run(void)
{
	bsp_mb_slave_handle();

	uint32_t ms = (uint32_t)(HAL_GetTick() - tot1_period);
	if(ms >= 1000)
	{
		tot1_period = HAL_GetTick();
		tot1++;
		mb_log("Total: %lld\r\n", tot1);

		uint16_t* tmp = (uint16_t*)&tot1;
		bsp_mb_input_reg_set(0, tmp[0]);
		bsp_mb_input_reg_set(1, tmp[1]);
		bsp_mb_input_reg_set(2, tmp[2]);
		bsp_mb_input_reg_set(3, tmp[3]);
	}
}
