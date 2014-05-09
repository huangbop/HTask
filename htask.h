#ifndef _HTASK_H_
#define _HTASK_H_

#define HT_NULL               ((void *)0)

#define SRCPND                (*(volatile unsigned *)0x4a000000)
#define SUBSRCPND             (*(volatile unsigned *)0x4a000018)
#define INTMODE               (*(volatile unsigned *)0x4a000004)
#define INTMASK               (*(volatile unsigned *)0x4a000008)
#define INTSUBMASK            (*(volatile unsigned *)0x4a00001c)
#define INTPND                (*(volatile unsigned *)0x4a000010)
#define ALL_MASKED            (0xffffffff)
#define SUB_ALL_MASKED        (0x7ff)

/* clock */
#define LOCKTIME              (*(volatile unsigned *)0x4c000000)
#define MPLLCON               (*(volatile unsigned *)0x4c000004)
#define UPLLCON               (*(volatile unsigned *)0x4c000008)
#define CLKCON                (*(volatile unsigned *)0x4c00000c)
#define CLKDIVN               (*(volatile unsigned *)0x4c000014)

/* uart */
#define GPHCON                (*(volatile unsigned *)0x4c000070)
#define GPHUP                 (*(volatile unsigned *)0x4c000078)
#define U0BASE                (*(volatile unsigned *)0x50000000)

/* interrupt service routine */
#define MAX_HANDLER           32

typedef void (*ht_isr_handler)(int vector, void *param);

struct ht_isr_desc {
	ht_isr_handler handler;
	void *param;
};


/* utilities */
extern void ht_memset(void *buf, char val, int len);

/* cpu */
extern void ht_cpu_enable_icache(void);
extern void ht_cpu_enable_dcache(void);

/* interrupt */
extern void ht_init_interrupt(void);
extern void ht_install_interrupt(int vector, ht_isr_handler handler, void *param);

/* board */
extern void ht_init_board(void);

/* init board */
extern void ht_init_clock(void);
extern void ht_init_uart(void);

#endif /* _HTASK_H_ */
