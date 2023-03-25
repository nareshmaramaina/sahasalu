TARGET_MODULE:=simple-module
# If we running by kernel building system
	$(TARGET_MODULE)-objs := main.o device_file.o
	obj-m := $(TARGET_MODULE).o

CFLAG   :=ARCH=arm CROSS_COMPILE=/opt/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-
# If we are running without kernel build system
	#BUILDSYSTEM_DIR?=/lib/modules/$(shell uname -r)/build
KDIR=/root/kernel_src/linux-3.0.35_1170_lcd


all : 
# run kernel build system to make module
	$(MAKE) -C $(KDIR) M=`pwd` modules $(CFLAG)

clean:
# run kernel build system to cleanup in current directory
	$(MAKE) -C $(KDIR) M=`pwd` clean

load:
	insmod ./$(TARGET_MODULE).ko

unload:
	rmmod ./$(TARGET_MODULE).ko


