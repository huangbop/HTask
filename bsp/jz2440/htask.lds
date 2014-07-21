/*
 * Copyright (C) 2014 Huang Bo
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x00000000;
	
	. = ALIGN(4);
	.text :
	{
		cpu/s3c2440/start.o(.text)
		cpu/s3c2440/clock.o(.text)
		bsp/jz2440/nand.o(.text)
		*(.text)
	}

	. = ALIGN(4);
	.rodata : { *(.rodata*) }

	. = ALIGN(4);
	.data : { *(.data*) }

	. = ALIGN(4);
	.nobss : { *(.nobss*) }

	. = ALIGN(4);
	__bss_start = .;
	.bss : { *(.bss) }
	__bss_end = .;
}
