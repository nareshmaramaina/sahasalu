obj-m	:= Ioctl.o
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:=$(shell pwd)

CFLAG	:=
default:
	$(MAKE)   -C $(KDIR) SUBDIRS=$(PWD) modules $(CFLAG) 

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean 


