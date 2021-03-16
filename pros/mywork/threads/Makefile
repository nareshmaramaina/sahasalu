obj-m := KKKK.o

#KDIR=/lib/modules/$(shell uname -r)/build/
KDIR=/u01/ksrc/KPDS_Kernel/
CFLAG := CROSS_COMPILE=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi- ARCH=arm

all:
	#$(MAKE) -C $(KDIR) M=$(PWD) modules 
	$(MAKE) -C $(KDIR) M=$(PWD) modules $(CFLAG)
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean 
