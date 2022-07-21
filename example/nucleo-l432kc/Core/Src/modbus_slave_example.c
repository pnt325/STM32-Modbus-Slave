/*
 * modbus_slave_example.c
 *
 *  Created on: Jul 21, 2022
 *      Author: phatn
 */

#include "../../lib/bsp_mb_slave.h"

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
	bsp_mb_input_reg_set(0, 1);
	bsp_mb_input_reg_set(1, 2);
	bsp_mb_input_reg_set(2, 3);
	bsp_mb_input_reg_set(3, 4);

	// Update holding register
	bsp_mb_holding_reg_set(0, 5);
	bsp_mb_holding_reg_set(1, 6);
	bsp_mb_holding_reg_set(2, 7);
	bsp_mb_holding_reg_set(3, 8);
}

void modbus_slave_example_run(void)
{
	bsp_mb_slave_handle();
}
