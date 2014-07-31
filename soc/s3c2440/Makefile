
include $(TOPDIR)/config.mk

lib	:= libs3c2440.a
objs	:= start.o clock.o serial.o

all: 	$(lib)

$(lib):	$(objs)
	$(AR) $(ARFLAGS) $@ $(objs)



