/*
 * Copyright (C) 2014 Huang Bo
 */

#include "s3c2440.h"

void uart_init(void)
{
	gpio.GPHCON |= 0xa0;	/* only set uart0 */

	uart.ulcon = 0x3;	/* 8-bits */
	uart.ucon = 0x5;	/* DMA mode */
	uart.ubrdiv = 26;
}

void uart_putc(char c)
{
	while (!(uart.utrstat & 0x2));
	
	uart.utxh = c;
}
