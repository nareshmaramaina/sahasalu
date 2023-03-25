obj-m := module_param.o

KDIR=/lib/modules/$(shell uname -r)/build
#KDIR=/root/kernel_src/linux-3.0.35_1170_lcd/
#CFLAG := CROSS_COMPILE=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi- ARCH=arm
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules 
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean 

