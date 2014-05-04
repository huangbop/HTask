#ifndef _HTASK_H_
#define _HTASK_H_


#define SRCPND                (*(volatile unsigned *)0x4a000000)
#define SUBSRCPND             (*(volatile unsigned *)0x4a000018)
#define INTMODE               (*(volatile unsigned *)0x4a000004)
#define INTMASK               (*(volatile unsigned *)0x4a000008)
#define INTSUBMASK            (*(volatile unsigned *)0x4a00001c)
#define INTPND                (*(volatile unsigned *)0x4a000010)
#define ALL_MASKED            (0xffffffff)
#define SUB_ALL_MASKED        (0x7ff)

/* interrupt service routine */
#define MAX_HANDLER           32

typedef void (*ht_isr_handler)(int vector, void *param);

struct ht_isr_desc
{
	ht_isr_handler handler;
	void *param;
};


/* utilities */
extern void ht_memset(void *buf, char val, int len);

/* cpu */
extern void ht_cpu_enable_icache();
extern void ht_cpu_enable_dcache();

/* interrupt */
extern void ht_init_interrupt();

#endif /* _HTASK_H_ */
