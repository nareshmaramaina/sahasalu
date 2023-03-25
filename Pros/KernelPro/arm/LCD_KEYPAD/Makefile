
#obj-m   :=i.MX6SLFirst.o
#obj-m   :=test.o
obj-m   := lcdkp_io.o
#KDIR    := /home/sololite/ltib/rpm/BUILD/linux-3.0.35/
#KDIR    := /home/sololite/GL11/KERNEL/linux-3.0.35/
#KDIR    := /home/kanth/L3.0.35_4.1.0_130816_source/ltib/ltib/rpm/BUILD/linux-3.0.35
KDIR    := /home/kernel-1.4/linux-3.0.35
PWD     :=$(shell pwd)
CFLAG   :=ARCH=arm CROSS_COMPILE=/opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-fsl-linux-gnueabi-
default:
	$(MAKE)   -C $(KDIR) SUBDIRS=$(PWD) modules $(CFLAG)
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

