/*
 * Copyright (C) 2014 Huang Bo
 */
#ifndef _SERIAL_H_
#define _SERIAL_H_

int serial_init(void);

void serial_putc(const char c);

void serial_puts(const char *s);

#endif /* _SERIAL_H_ */

