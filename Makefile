#
# Copyright (C) 2014 Huang Bo
#

VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 0
EXTRAVERSION = 
HTASK_VERSION = $(VERSION).$(PATCHLEVEL).$(SUBLEVEL).$(EXTRAVERSION)

export TOPDIR := $(CURDIR)

include $(TOPDIR)/config.mk

LIBS	:= cpu/s3c2440/libs3c2440.a bsp/jz2440/libjz2440.a src/libsrc.a

all:	htask.elf

htask.elf: 	$(LIBS)
	$(LD) $(LDFLAGS) --start-group $(LIBS) --end-group -Map htask.map -o htask.elf

$(LIBS):
	$(MAKE) -C $(dir $@)

clean:
	find . -name *.o -o -name *~ -o -name *.elf -o -name *.bin -o -name *.a |xargs rm -f 
