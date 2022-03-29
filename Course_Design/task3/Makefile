obj-m := yizumi.o
    PWD := $(shell pwd)
    KERNELDIR := /usr/src/linux-4.14.267
all:
	make -C $(KERNELDIR) M=$(PWD) modules
 
 
.PHONY: clean
clean:
	rm -rf *.o *~ core *.ko *.mod.c modules.order Module.symvers

