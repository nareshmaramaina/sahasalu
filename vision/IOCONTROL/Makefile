obj-m   :=imx_iocon.o
#KDIR    := /u03/DOP_NEW/kernel/old_kernel/linux-3.0.35_dop/
#KDIR    := /u03/DOP_NEW/kernel/linux-3.0.35_dop/
KDIR    :=/root/kernel_src/linux-3.0.35_1170_lcd/ 
PWD     :=$(shell pwd)
CFLAG	:=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-gcc
#CFLAG   :=ARCH=arm CROSS_COMPILE=/opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-
default:
	$(MAKE)   -C $(KDIR) SUBDIRS=$(PWD) modules $(CFLAG)
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

