/*
 * Copyright (C) 2014 Huang Bo
 */
#include "s3c2440.h"

void clock_init(void)
{
	clock.locktime = 0xffffffff;
	
	/* FCLK:HCLK:PCLK = 1:4:8 */
	clock.clkdivn = 0x5;
	
	/* 12.0000MHz to 400.00MHz */
	clock.mpllcon = (0x5c << 12) | (1 << 4) | 1;
	
	__asm__ __volatile__ (
		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr r0, r0, #0xc0000000\n"
		"mcr p15, 0, r0, c1, c0, 0");
}
