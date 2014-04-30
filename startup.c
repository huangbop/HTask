/*
 * Copyright (C) 2014 Huang Bo
 */

/* set stack */
unsigned char _irq_stack[1024];
unsigned char _fiq_stack[1024];
unsigned char _abt_stack[1024];
unsigned char _und_stack[1024];
unsigned char _svc_stack[1024];

int _htask_startup()
{
  int i = 0;

  i = i * i;

  return 0;
}
