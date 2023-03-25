CC= gcc

INCLUDE= .

CFLAGS= -g -Wall

INSTDIR= /home/naresh/

sample:	main.o fun1.o fun2.o

	$(CC) -o sample main.o fun1.o fun2.o

main.o: main.c fun.h naresh.h

	$(CC) -I$(INCLUDE) $(CFLAGS) -c  main.c

fun1.o: fun1.c

	$(CC) -I$(INCLUDE) $(CFLAGS) -c  fun1.c

fun2.o: fun2.c

	$(CC) -I$(INCLUDE) $(CFLAGS) -c  fun2.c

clean:

	rm *.o	
install: sample
	if [ -d $(INSTDIR) ];then \
	cp sample $(INSTDIR);\
	chmod a+x $(INSTDIR)/sample;\
	chmod og-w $(INSTDIR)/sample;\
	echo “Installed in $(INSTDIR)”;\
	else \
	echo “Sorry, $(INSTDIR) does not exist”;\
	fi
