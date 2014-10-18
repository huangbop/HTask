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

struct rt_event the_event;

void thread_a_entry(void *param)
{
	static int flag = 0;

	while (1) {
		flag = !flag;
		rt_kprintf("It's aaa, %d \n", flag);

		if (flag)
			rt_event_send(&the_event, (1 << 3));
		else 
			rt_event_send(&the_event, (1 << 7));
	}
}

void thread_b_entry(void *param)
{
	unsigned recv;

	while (1) {
		if (rt_event_recv(&the_event, 1 << 3, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, 
				  RT_WAITING_FOREVER, &recv) == RT_EOK) {
			rt_kprintf("It's bbb, %d\n", recv);
		}
	}
}

void thread_c_entry(void *param)
{
	unsigned recv;
	
	while (1) {
		if (rt_event_recv(&the_event, 1 << 7, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, 
			      RT_WAITING_FOREVER, &recv) == RT_EOK) {
			rt_kprintf("It's ccc, %d\n", recv);			
		}
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

	rt_event_init(&the_event, "the event", RT_IPC_FLAG_FIFO);
	
	res = rt_thread_init(&thread_a, "aaa", thread_a_entry, RT_NULL,
			     &thread_a_stack[0], 1024, 10, 5);

	res = rt_thread_init(&thread_b, "bbb", thread_b_entry, RT_NULL,
			     &thread_b_stack[0], 1024, 10, 6);

	res = rt_thread_init(&thread_c, "ccc", thread_c_entry, RT_NULL,
			     &thread_c_stack[0], 1024, 10, 7);

	/* res = rt_thread_init(&thread_d, "ddd", thread_d_entry, RT_NULL, */
	/* 		     &thread_d_stack[0], 1024, 10, 3); */
	

	rt_thread_startup(&thread_a);
	rt_thread_startup(&thread_b);
	rt_thread_startup(&thread_c);
	/* rt_thread_startup(&thread_d); */
}

