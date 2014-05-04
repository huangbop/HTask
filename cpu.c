

#include "htask.h"

#define ICACHE_MASK (1 << 12)
#define DCACHE_MASK (1 << 2)

__inline__ void enable_cache(mask)
{
	__asm__ __volatile__(
		"mrc p15, 0, r0, c1, c0, 0\n\t"
		"orr r0, r0, %0\n\t"
		"mcr p15, 0, r0, c1, c0, 0"
		:
		:"r"(mask)
		:);
	
}

__inline__ void disable_cache(mask)
{
	__asm__ __volatile__(
		"mrc p15, 0, r0, c1, c0, 0\n\t"
		"bic r0, r0, %0\n\t"
		"mcr p15, 0, r0, c1, c0, 0"
		:
		:"r"(mask)
		:);
	
}

void ht_cpu_enable_icache()
{
	enable_cache(ICACHE_MASK);
	
}

void ht_cpu_enable_dcache()
{
	enable_cache(DCACHE_MASK);

}
