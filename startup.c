/*
 * Copyright (C) 2014 Huang Bo
 */

#include "htask.h"
#include "serial.h"

void clock_init(void)
{
	struct clock_power *const clk_pow = get_base_clock_power();

	clk_pow->locktime = 0xffffffff;
	
	/* 12.0000MHz to 400.00MHz */
	clk_pow->mpllcon = (0x5c << 12) | (1 << 4) | 1;
	
	/* FCLK:HCLK:PCLK = 1:4:8 */
	clk_pow->clkdivn = 0x5;
	__asm__ __volatile__ (
		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr r0, r0, #0xc0000000\n"
		"mcr p15, 0, r0, c1, c0, 0");
}

void ht_startup(void)
{
	serial_init();

	main();
}
