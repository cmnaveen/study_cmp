obj-m:=usb_camera.o

dummy:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules
	gcc -o app app.c -Wall

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
	rm app
