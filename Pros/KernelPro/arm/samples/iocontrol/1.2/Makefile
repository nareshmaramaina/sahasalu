obj-m   :=imx_iocon.o
#obj-m   :=gl865_reset.o
#KDIR    :=/u03/BANDHAN/working/kernel/1.2/linux-3.0.35
KDIR    :=/home/arun/linux-3.0.35_dop
PWD     :=$(shell pwd)
CFLAG   :=ARCH=arm CROSS_COMPILE=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-
default:
	$(MAKE)   -C $(KDIR) SUBDIRS=$(PWD) modules $(CFLAG)
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

