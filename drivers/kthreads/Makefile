#if called directly from the command line, invoke the kernel build system.
#ifeq ($(KERNELRELEASE),)
 
   
#default: module app_ioctl
 
obj-m:= my_LL.o
module:
	make -C /lib/modules/$(shell uname -r)/build  M=$(PWD) modules
 
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
#	${RM} app_ioctl
 
# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
#else
 
 


