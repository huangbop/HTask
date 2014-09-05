/*
 * Copyright (C) 2014 Huang Bo
 */

#include "s3c2440.h"

void led_init(void)
{
	gpio.GPFCON = 0x1500;	/* output with 4,5,6 */
}


/* just accept 4, 5, 6 */
void led_on(unsigned which)
{
	if (which >= 4 && which <= 6)
		gpio.GPFDAT &= ~(1 << which);
}
/* just accept 4, 5, 6 */
void led_off(unsigned which)
{
	if (which >= 4 && which <= 6)
		gpio.GPFDAT |= (1 << which);
}
