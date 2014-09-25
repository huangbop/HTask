/*
 * Copyright (C) 2014 Huang Bo
 */
#include "s3c2440.h"

#define OSC_FREQ 12000000

#if OSC_FREQ == 12000000
/* 12MHz to 400MHz */
#define MPLL_MDIV 92
#define MPLL_PDIV 1
#define MPLL_SDIV 1
#define HDIVN 2 		/* HCLK = FCLK / 4 */
#define PDIVN 1			/* PCLK = HCLK / 2 */
#endif


void clock_init(void)
{
	clock.locktime = 0xffffffff;

	/* 12.0000MHz to 400.00MHz */
	clock.mpllcon = (MPLL_MDIV << 12) | (MPLL_PDIV << 4) | MPLL_SDIV;
	
	/* FCLK:HCLK:PCLK = 1:4:8 */
	clock.clkdivn = (HDIVN << 1) | PDIVN;
}
