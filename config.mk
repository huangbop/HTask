
ifeq ($(PREFIX),)
PREFIX	= arm-none-eabi-
endif

CC	= $(PREFIX)gcc
AR	= $(PREFIX)ar
LD	= $(PREFIX)ld
OBJDUMP	= $(PREFIX)objdump
OBJCOPY	= $(PREFIX)objcopy

LDS	:= bsp/jz2440/htask.lds

CPPFLAGS := -DTEXT_BASE=0x33f80000 -I$(TOPDIR)/include -I$(TOPDIR)/cpu/s3c2440\
	-I$(TOPDIR)/bsp/jz2440 -I$(TOPDIR)/src
AFLAGS := -g -O0 $(CPPFLAGS)
CFLAGS := -g -O0
ARFLAGS = crv
LDFLAGS	= -Bstatic -T $(LDS) -Ttext 0x33f80000 

%.o:	%.S
	$(CC) $(AFLAGS) -c -o $@ $<

