obj-m := naresh.o

KDIR=/lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
#	@rm -rf a.out
	$(MAKE) -C $(KDIR) M=$(PWD) clean
