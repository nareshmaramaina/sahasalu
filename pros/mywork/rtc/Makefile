obj-m:= rtc_sysfs.o

KDIR := /root/kernel_src/linux-3.0.35_rjpds_lcd/
CFLAG := ARCH=arm CROSS_COMPILE=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-
#KDIR=/root/kernel_src/linux-3.0.35_rjpds_lcd/
#KDIR=/root/kernel_src/linux-3.0.35_1170_lcd/
#KDIR=/lib/modules/$(shell uname -r)/build
#CC=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-gcc
#ARCH=arm
all:	
	$(MAKE) -C $(KDIR) M=$(PWD) modules  $(CFLAG)	

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
