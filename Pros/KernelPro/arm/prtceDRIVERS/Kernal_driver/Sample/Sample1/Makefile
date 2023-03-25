	
	obj-m   :=king.o
	king-objs :=driver.o device_file.o
KDIR    :=/root/kernel_src/linux-3.0.35_1170_lcd/
PWD     :=$(shell pwd)
CFLAG   :=ARCH=arm CROSS_COMPILE=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-
default:
	$(MAKE)   -C $(KDIR) SUBDIRS=$(PWD) modules $(CFLAG)
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
