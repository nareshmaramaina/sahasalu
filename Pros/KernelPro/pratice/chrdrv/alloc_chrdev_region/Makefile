obj-m := kk.o

KSRC=/lib/modules/$(shell uname -r)/build/

all:
	$(MAKE) -C $(KSRC) M=$(PWD) modules
clean:
	$(MAKE) -C $(KSRC) M=$(PWD) clean 
