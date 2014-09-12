/*
 * Copyright (C) 2014 Huang Bo
 */

#include "rtthread.h"
#include "s3c2440.h"

#define UART_TX_EMPTY (1 << 1)
#define UART_RX_READY (1 << 0)

static struct rt_device uart0;

extern pclk;

void uart_init(void)
{
	gpio.GPHCON |= 0xa0;	/* only set uart0 */

	uart.ulcon = 0x3;	/* 8-bits */
	uart.ucon = 0x5;	/* DMA mode */
	uart.ubrdiv = (int)(pclk / (115200 * 16)) - 1;
}

rt_size_t uart_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
	rt_off_t _pos = pos;

	while (pos < size) {
		if (uart.utrstat & UART_RX_READY) 
			((char *)buffer)[pos++] = uart.urxh;
	}
	
	return size - _pos;
}

rt_size_t uart_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
	rt_off_t _pos = pos;

	while (pos < size) {
		while (!(uart.utrstat & UART_TX_EMPTY));
		uart.utxh = ((char *)buffer)[pos++]; 
	}
	
	return size - _pos;
}


void uart_register(void)
{
	uart0.type = RT_Device_Class_Char;
	uart0.init = RT_NULL;
	uart0.open = RT_NULL;
	uart0.close = RT_NULL;
	uart0.control = RT_NULL;

	uart0.read = uart_read;
	uart0.write = uart_write;
	
	rt_device_register(&uart0, "uart", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STREAM);
}
