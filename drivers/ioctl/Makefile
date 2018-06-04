ifneq ($(KERNELRELEASE),) 
   obj-m := ioctl_basic.o query_app.o  query_ioctl.o   user_ioctl_basic.o

else 

KERNELDIR ?= /lib/modules/$(shell uname -r)/build 

PWD := $(shell pwd)

default: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules  
endif 

