
include $(TOPDIR)/config.mk

lib	:= libjz2440.a
objs	:= nand.o serial.o main.o

all:	$(lib)

$(lib):	$(objs)
	$(AR) $(ARFLAGS) $@ $(objs)



