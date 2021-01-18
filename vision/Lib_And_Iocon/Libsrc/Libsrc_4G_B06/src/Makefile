#CC=/opt/freescale/usr/local/gcc-4.6.2-glibc-2.13-linaro-multilib-2011.12/fsl-linaro-toolchain/bin/arm-none-linux-gnueabi-gcc
CC=arm-none-linux-gnueabi-gcc

OBJS=scr.o printer.o magswipe.o barcode_api.o lcdcontrol.o iomisc.o sam_api.o gsm_gps_api.o rfid_api.o rtc.o
#OBJS=scr.o printer.o magswipe.o gsm_gps.o  barcode_api.o lcdcontrol.o gps_api.o iomisc.o sam_api.o gsm_api.o rfid_api.o rtc.o


FLAGFPIC=
FLAGGDB=
IDIR=../include
LIB=../lib
GDB="no"
ifeq ($(GDB),"yes")
FLAGGDB=-g
endif
 

#SUBDIR=$(PWD)/optical/samples
#LIB=$(PWD)/LIB

#SHAREDLIB="yes"
#ifeq ($(SHAREDLIB),"yes")
FLAGFPIC=-fPIC

app:$(OBJS)
	$(CC) -shared -o $(LIB)/libgl11pos.so -L../lib/sam_lib -lpcsclite  $(OBJS) -lrt -lpthread  -L ../lib/kf311_lib/ -lcrypto -L ../lib/kf311_lib/ -lkf311
	arm-none-linux-gnueabi-strip ../lib/libgl11pos.so


printer.o:printer/printer.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) printer/printer.c
rfid_api.o:rfid/rfid_api.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) rfid/rfid_api.c
magswipe.o:magswipe/magswipe.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) magswipe/magswipe.c
sam_api.o:sam/sam_api.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) sam/sam_api.c
barcode_api.o:barcode/barcode_api.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) barcode/barcode_api.c
scr.o:scr/scr.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) scr/scr.c
rtc.o:rtc/rtc.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) rtc/rtc.c
gsm_gps_api.o:gsm-gps/gsm_gps_api.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) gsm-gps/gsm_gps_api.c
iomisc.o:miscall/iomisc.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) miscall/iomisc.c    
lcdcontrol.o:lcd/lcdcontrol.c
	$(CC) -I $(IDIR) -c $(FLAGGDB) $(FLAGFPIC) lcd/lcdcontrol.c

clean:
	rm -f *.o $(LIB)/*.so

