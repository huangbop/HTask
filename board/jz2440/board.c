/*
 * Copyright (C) 2014 Huang Bo
 */

#include "rtthread.h"
#include "s3c2440.h"

extern void clock_init(void);
extern void uart_init(void);
extern void led_init(void);

/* init timer4 for system tick */
void timer_init(void)
{
	/* timer4, pre = 15+1 */
	TCFG0 &= 0xffff00ff;
	TCFG0 |= 15 << 8;

	/* all are interrupt mode,set Timer 4 MUX 1/4 */
	TCFG1  &= 0xfff0ffff;
	TCFG1  |= 0x00010000;

	/* TCNTB4 = (rt_int32_t)(50000000 / (4 * 16 * 100)) - 1; */
	TCNTB4 = 400;
	/* manual update */
	TCON = TCON & (~(0x0f<<20)) | (0x02<<20);

	rt_hw_interrupt_umask(INTTIMER4);
	
	/* start timer4, reload */
	TCON = TCON & (~(0x0f<<20)) | (0x05<<20);
}

void board_init(void)
{
	clock_init();

	uart_init();	
	uart_register();
	rt_console_set_device("uart");
	
	led_init();

	timer_init();
}
