/*
 * Copyright (C) 2014 Huang Bo
 */

#include "rtthread.h"

struct rt_thread thread_a;
struct rt_thread thread_b;
struct rt_thread thread_c;
struct rt_thread thread_d;

unsigned char thread_a_stack[1024];
unsigned char thread_b_stack[1024];
unsigned char thread_c_stack[1024];
unsigned char thread_d_stack[1024];

struct rt_mailbox the_mb;
char mb_buf[40];

void thread_a_entry(void *param)
{
	unsigned c = 'x';

	while (1) {
		rt_mb_send_wait(&the_mb, c, RT_WAITING_FOREVER);
		rt_kprintf("It's aaa\n");
		
	}
}

void thread_b_entry(void *param)
{
	unsigned c;

	while (1) {
		rt_mb_recv(&the_mb, &c, RT_WAITING_FOREVER);
		rt_kprintf("recv %c from b\n", c);
		
	}
}

void thread_c_entry(void *param)
{
	unsigned c;

	while (1) {
		rt_mb_recv(&the_mb, &c, RT_WAITING_FOREVER);
		rt_kprintf("recv %c from c\n", c);
	}
}

void thread_d_entry(void *param)
{
	while (1) {
		
		rt_kprintf("It's ddd\n");
		

	}
}

void rt_application_init(void)
{
	rt_err_t res;

	rt_mb_init(&the_mb, "the mb", mb_buf, sizeof(mb_buf)/4, RT_IPC_FLAG_FIFO);
	
	res = rt_thread_init(&thread_a, "aaa", thread_a_entry, RT_NULL,
			     &thread_a_stack[0], 1024, 9, 5);

	res = rt_thread_init(&thread_b, "bbb", thread_b_entry, RT_NULL,
			     &thread_b_stack[0], 1024, 10, 5);

	res = rt_thread_init(&thread_c, "ccc", thread_c_entry, RT_NULL,
			     &thread_c_stack[0], 1024, 10, 5);

	/* res = rt_thread_init(&thread_d, "ddd", thread_d_entry, RT_NULL, */
	/* 		     &thread_d_stack[0], 1024, 10, 3); */
	

	rt_thread_startup(&thread_a);
	rt_thread_startup(&thread_b);
	rt_thread_startup(&thread_c);
	/* rt_thread_startup(&thread_d); */
}

