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
CFLAGS = -g 
LDFLAGS = 

BIN := htask.bin
DIS := htask.dis
ELF := htask.elf

LDS := htask.lds

obj-y := start.o startup.o main.o serial.o nand.o

all: 	$(DIS)

$(DIS):	$(ELF)
	$(OBJDUMP) -S $(ELF) > $(DIS)
	$(OBJCOPY) -S -O binary $(ELF) $(BIN)

$(ELF): $(obj-y) $(LDS)
	arm-none-eabi-gcc -g -c start.S -o start.o
	$(LD) $(LDFLAGS)   -T $(LDS) $(obj-y) -o $@

clean:
	rm -rf $(obj-y) *.elf *.dis
