obj-m   :=imx_iocon.o
#KDIR    :=/u02/Kpds/linux-3.0.35_rjpds_lcd
 
KDIR    :=/u01/Builds_new/1105/Kernel_291218/
PWD     :=$(shell pwd)
CFLAG   :=ARCH=arm CROSS_COMPILE=/opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-
default:
	$(MAKE)   -C $(KDIR) SUBDIRS=$(PWD) modules $(CFLAG)
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

