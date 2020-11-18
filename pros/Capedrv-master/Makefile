obj-m := at24_sys.o

#KDIR = <path-to-kernel-source>
#KDIR = /home/shrikant/embedded_and_linux/porting/builds/linux-4.4.94_03-april-2018
KDIR = /home/shrikant/bbb_builds/linux-4.12

all:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

