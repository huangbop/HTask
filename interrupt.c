
#include "htask.h"

/* interrupt service table */
struct ht_isr_desc isr_table[MAX_HANDLER];

/* default handler */
void ht_default_handler(int vector, void *param)
{
	
}

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
	int i;

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

	/* init interrupt service table */
	ht_memset(isr_table, 0, sizeof(isr_table));
	for (i = 0; i < MAX_HANDLER; i++) {
		isr_table[i].handler = ht_default_handler;
	}

}

void ht_install_interrupt(int vector, ht_isr_handler handler, void *param)
{
	isr_table[vector].handler = handler;
	isr_table[vector].param = param;
}
