include *.h 
CC= gcc

INCLUDE= -I ../include

CFLAGS= -g -Wall  

LIB=-L../lib

#sample: main.c fun1.c fun2.c
#	$(CC) $(CFLAGS) $@.c -o $@

sample: main.c fun1.c fun2.c 
	$(CC) $(CFLAGS) $(INCLDUE) $< -c 
	$(CC) $(CFLAGS) $(INCLDUE) main.o -o $@ 






#	$(CC) $(CFLAGS) $(INLCUDE)  -c $*.c

#	$(CC) $(CFLAGS) $(INCLUDE) $(LIB) -lfun -c $*.c

#alternatively:
#.o.cpp:
#$(CC) $(CFLAGS) -c $*.c

clean:
	rm sample	
