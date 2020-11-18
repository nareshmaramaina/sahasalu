
#obj-m   :=i.MX6SLFirst.o
#obj-m   :=test.o
#obj-m   :=imx_tpd.o
obj-m   :=imx_mscrd.o
KDIR    :=/u01/IMX6/Back-up/kernel/linux-3.0.35 
PWD     :=$(shell pwd)
CFLAG   :=ARCH=arm CROSS_COMPILE=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-fsl-linux-gnueabi-
default:
	$(MAKE)   -C $(KDIR) SUBDIRS=$(PWD) modules $(CFLAG)
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean

