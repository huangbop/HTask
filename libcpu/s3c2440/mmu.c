/*
 * Copyright (C) 2014 Huang Bo
 */

#include <rtthread.h>
#include "s3c2440.h"

#define _MMUTT_STARTADDRESS	 0x31000000

#define DESC_SEC		(0x2|(1<<4))
#define CB				(3<<2)  //cache_on, write_back
#define CNB				(2<<2)  //cache_on, write_through
#define NCB				(1<<2)  //cache_off,WR_BUF on
#define NCNB				(0<<2)  //cache_off,WR_BUF off
#define AP_RW			(3<<10) //supervisor=RW, user=RW
#define AP_RO			(2<<10) //supervisor=RW, user=RO

#define DOMAIN_FAULT	(0x0)
#define DOMAIN_CHK		(0x1)
#define DOMAIN_NOTCHK	(0x3)
#define DOMAIN0			(0x0<<5)
#define DOMAIN1			(0x1<<5)

#define DOMAIN0_ATTR	(DOMAIN_CHK<<0)
#define DOMAIN1_ATTR	(DOMAIN_FAULT<<2)

#define RW_CB		(AP_RW|DOMAIN0|CB|DESC_SEC)
#define RW_CNB		(AP_RW|DOMAIN0|CNB|DESC_SEC)
#define RW_NCNB		(AP_RW|DOMAIN0|NCNB|DESC_SEC)
#define RW_FAULT	(AP_RW|DOMAIN1|NCNB|DESC_SEC)

#ifdef __CC_ARM
void mmu_setttbase(rt_uint32_t i)
{
    __asm
    {
        mcr p15, 0, i, c2, c0, 0
    }
}

void mmu_set_domain(rt_uint32_t i)
{
    __asm
    {
        mcr p15,0, i, c3, c0,  0
    }
}

void mmu_enable()
{
    /* register */ rt_uint32_t value;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int g = 0;

	int h = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	int n = 0;

	int o = 0;
	int p = 0;
	int q = 0;
	
	a++;
	b++;
	c++;
	d++;
	e++;
	f++;
	g++;

	h++;
	i++;
	j++;
	k++;
	l++;
	m++;
	n++;

	o++;
	p++;
	q++;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x01
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x01
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_icache()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x1000
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_dcache()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x04
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_icache()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x1000
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_dcache()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x04
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_enable_alignfault()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        orr value, value, #0x02
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_disable_alignfault()
{
    register rt_uint32_t value;

    __asm
    {
        mrc p15, 0, value, c1, c0, 0
        bic value, value, #0x02
        mcr p15, 0, value, c1, c0, 0
    }
}

void mmu_clean_invalidated_cache_index(int index)
{
    __asm
    {
        mcr p15, 0, index, c7, c14, 2
    }
}

void mmu_invalidate_tlb()
{
    register rt_uint32_t value;

    value = 0;
    __asm
    {
        mcr p15, 0, value, c8, c7, 0
    }
}

void mmu_invalidate_icache()
{
    register rt_uint32_t value;

    value = 0;

    __asm
    {
        mcr p15, 0, value, c7, c5, 0
    }
}
#endif

void mmu_setmtt(int vaddrStart,int vaddrEnd,int paddrStart,int attr)
{
    volatile rt_uint32_t *pTT;
    volatile int i,nSec;
    pTT=(rt_uint32_t *)_MMUTT_STARTADDRESS+(vaddrStart>>20);
    nSec=(vaddrEnd>>20)-(vaddrStart>>20);
    for(i=0;i<=nSec;i++)
    {
		*pTT = attr |(((paddrStart>>20)+i)<<20);
		pTT++;
    }
}

void rt_hw_mmu_init(void)
{
	int i,j;
	//========================== IMPORTANT NOTE =========================
	//The current stack and code area can't be re-mapped in this routine.
	//If you want memory map mapped freely, your own sophiscated mmu
	//initialization code is needed.
	//===================================================================

#if 0
	mmu_disable_dcache();
	mmu_disable_icache();

	//If write-back is used,the DCache should be cleared.
	for(i=0;i<64;i++)
		for(j=0;j<8;j++)
			mmu_clean_invalidated_cache_index((i<<26)|(j<<5));

	mmu_invalidate_icache();

	//To complete mmu_Init() fast, Icache may be turned on here.
	mmu_enable_icache();

	mmu_disable();
	mmu_invalidate_tlb();

	//mmu_setmtt(int vaddrStart,int vaddrEnd,int paddrStart,int attr);
	mmu_setmtt(0x00000000,0x07f00000,0x00000000,RW_CNB);  //bank0
	mmu_setmtt(0x00000000,0x03f00000,(int)0x30000000,RW_CB);  //bank0
	mmu_setmtt(0x04000000,0x07f00000,0,RW_NCNB);  			//bank0
	mmu_setmtt(0x08000000,0x0ff00000,0x08000000,RW_CNB);  //bank1
	mmu_setmtt(0x10000000,0x17f00000,0x10000000,RW_NCNB); //bank2
	mmu_setmtt(0x18000000,0x1ff00000,0x18000000,RW_NCNB); //bank3
	//mmu_setmtt(0x20000000,0x27f00000,0x20000000,RW_CB); //bank4
	mmu_setmtt(0x20000000,0x27f00000,0x20000000,RW_NCNB); //bank4 for  DM9000
	mmu_setmtt(0x28000000,0x2ff00000,0x28000000,RW_NCNB); //bank5
	//30f00000->30100000, 31000000->30200000
	mmu_setmtt(0x30000000,0x30100000,0x30000000,RW_CB);	  //bank6-1
	mmu_setmtt(0x30200000,0x33e00000,0x30200000,RW_CB); //bank6-2

	mmu_setmtt(0x33f00000,0x34000000,0x33f00000,RW_NCNB);   //bank6-3
	mmu_setmtt(0x38000000,0x3ff00000,0x38000000,RW_NCNB); //bank7

	mmu_setmtt(0x40000000,0x47f00000,0x40000000,RW_NCNB); //SFR
	mmu_setmtt(0x48000000,0x5af00000,0x48000000,RW_NCNB); //SFR
	mmu_setmtt(0x5b000000,0x5b000000,0x5b000000,RW_NCNB); //SFR
	mmu_setmtt(0x5b100000,0xfff00000,0x5b100000,RW_FAULT);//not used
	mmu_setmtt(0x60000000,0x67f00000,0x60000000,RW_NCNB); //SFR
#endif
	mmu_setmtt(0x30000000,0x30100000,0x30000000, RW_CB); /* self */
		
	mmu_setmtt(0x56000000,0x56100000,(int)0x56000000, RW_CB); /* GPF */
	mmu_setmtt(0x51000000,0x51100000,(int)0x51000000, RW_CB); /* timer */
	mmu_setmtt(0x4a000000,0x4a100000,(int)0x4a000000, RW_CB); /* interrupt */
	mmu_setmtt(0x50000000,0x50100000,(int)0x50000000, RW_CB); /* uart */

	mmu_setmtt(0x00000000,0x00100000,(int)0x30000000, RW_CB); /* int vectors */



	/* mmu_setmtt(0x00000000,0x00100000,0x30000000,RW_CB);  */

	/* mmu_setmtt(0x56000000,0x56100000,0x56000000, RW_CB); /\* regs *\/ */
	
	
	mmu_setttbase(_MMUTT_STARTADDRESS);

	/* DOMAIN1: no_access, DOMAIN0,2~15=client(AP is checked) */
	/* mmu_set_domain(0x55555550|DOMAIN1_ATTR|DOMAIN0_ATTR); */
	mmu_set_domain(3);

	/* mmu_enable_alignfault(); */

	mmu_enable();
}

