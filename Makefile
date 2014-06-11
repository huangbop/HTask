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
OBJDUMP = $(PREFIX)objdump
OBJCOPY = $(PREFIX)objcopy
CFLAGS = -g -DTEXT_BASE=0x33f80000
LDFLAGS = -Ttext 0x33f80000

BIN := htask.bin
DIS := htask.dis
ELF := htask.elf

LDS := htask.lds

obj-y := start.o boot_init.o main.o serial.o lib.o

all: 	$(DIS)

$(DIS):	$(ELF)
	$(OBJDUMP) -S $(ELF) > $(DIS)
	$(OBJCOPY) -S -O binary $(ELF) $(BIN)

$(ELF): $(obj-y) $(LDS)
	arm-none-eabi-gcc -g -DTEXT_BASE=0x33f80000 -c start.S -o start.o
	$(LD) -T $(LDS) $(LDFLAGS) $(obj-y) -o $@

clean:
	rm -rf $(obj-y) *.elf *.dis
