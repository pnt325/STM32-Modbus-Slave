#include "mb_port.h"
#include "mb_assert.h"

__attribute__((weak)) void mb_port_start_recv(void* uart, uint8_t* buf, uint16_t buf_size)
{
    (void)uart;
    (void)buf;
    (void)buf_size;
    mb_assert(false);
}

__attribute__((weak)) void mb_port_start_send(void* uart, uint8_t* buf, uint16_t buf_size)
{
    (void)uart;
    (void)buf;
    (void)buf_size;
    mb_assert(false);
}

__attribute__((weak)) uint16_t mb_port_crc_calc(uint8_t* data, uint16_t data_len)
{
	(void)data;
	(void)data_len;
	mb_assert(false);
	return 0x0000;
}
