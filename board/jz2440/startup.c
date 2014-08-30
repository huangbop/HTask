/*
 * Copyright (C) 2014 Huang Bo
 */

#include <s3c2440.h>

extern void clock_init(void);
extern void led_init(void);
extern void uart_init(void);


int htask_startup(void)
{
	clock_init();

	led_init();
	
	uart_init();

	uart_putc('a');
	uart_putc('b');

	return 0;
}
