
#include "htask.h"




/* utilities */
void ht_memset(void *buf, char val, int len)
{
	char *p = (char *)buf;
	while (len--) {
		*p++ = val;
	}
}

void ht_init_interrupt()
{
	/* clear pending */
	SRCPND = 0x0;
	SUBSRCPND = 0x0;

	/* set all to IRQ */
	INTMODE = 0x0;

	/* masked all */
	INTMASK = ALL_MASKED;
	INTSUBMASK = SUB_ALL_MASKED;

	/* clear int pending */
	INTPND = ALL_MASKED;
}
