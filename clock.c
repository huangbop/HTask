
#include "htask.h"

void ht_set_mpll_clock(char sdiv, char pdiv, char mdiv)
{
	MPLLCON = sdiv | (pdiv<<4) | (mdiv<<12);
}

void ht_set_upll_clock(char sdiv, char pdiv, char mdiv)
{
	UPLLCON = sdiv | (pdiv<<4) | (mdiv<<12);
}

void ht_set_divider(char hdivn, char pdivn)
{
	CLKDIVN = (hdivn << 1) | pdivn;
}

void ht_init_clock(void)
{
	LOCKTIME = 0xffffffff;
	ht_set_mpll_clock(0, 4, 92);
	ht_set_upll_clock(1, 2, 56);
	ht_set_divider(2, 1);
}
