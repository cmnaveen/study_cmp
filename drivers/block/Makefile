# If called directly from the command line, invoke the kernel build system.
obj-m:=blck.o 
KERNEL_SOURCE := /usr/src/linux-headers-4.4.0-31-generic
PWD := $(shell pwd)
 
module:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules
 
clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) clean
 
# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
