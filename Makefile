#
# Copyright (C) 2014 Huang Bo
#

VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION = 
HTASK_VERSION = $(VERSION).$(PATCHLEVEL).$(SUBLEVEL).$(EXTRAVERSION)

ifeq ($(PREFIX),)
PREFIX = arm-none-eabi-
endif

CC = $(PREFIX)gcc
LD = $(PREFIX)ld
CFLAGS = -g
LDFLAGS = 

all:	htask.elf

htask.elf: start.o
	$(LD) $(LDFLAGS) -T htask.lds $< -o $@

start.o: start.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o htask.elf
