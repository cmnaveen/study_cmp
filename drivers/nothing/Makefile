
obj-m += fcd_split2.o


INC_DIR =../nothing

#SRC_DIR =../dvb-usb/


#INC :=-I/home/naveen/naveenreddy/uvc_change/all/drivers/media/usb/dvb-usb/

#module:
all :
	   
	make -C /lib/modules/$(shell uname -r)/build $(INC_DIR)  M=$(PWD) modules

clean:
	   make -C /lib/modules/$(shell uname -r)/build $(INC_DIR) M=$(PWD) clean


