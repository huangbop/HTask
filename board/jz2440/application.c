/*
 * Copyright (C) 2014 Huang Bo
 */

#include "rtthread.h"

struct rt_thread thread_a;
struct rt_thread thread_b;

unsigned char thread_a_stack[1024];
unsigned char thread_b_stack[1024];

void thread_a_entry(void *param)
{
	while (1) {
		rt_kprintf("It's aaa\n");
	}
}

void thread_b_entry(void *param)
{
	while (1) {
		rt_kprintf("It's bbb\n");
	}
}

void rt_application_init(void)
{
	rt_err_t res;
	
	res = rt_thread_init(&thread_a, "aaa", thread_a_entry, RT_NULL,
			     &thread_a_stack[0], 1024, 10, 1);

	res = rt_thread_init(&thread_b, "bbb", thread_b_entry, RT_NULL,
			     &thread_b_stack[0], 1024, 11, 1);
	

	rt_thread_startup(&thread_a);
	rt_thread_startup(&thread_b);
}

