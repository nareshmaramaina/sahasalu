include ../../Makefile.inc

P=threads/part4/
all:
	${GCC} pthread_once.c -lpthread -o pthread_once ${ECHO}pthread_once.c
	${GCC} thrcancel1.c -lpthread -o thrcancel1 ${ECHO}thrcancel1.c
	${GCC} thrcancel2.c -lpthread -o thrcancel2 ${ECHO}thrcancel2.c
	${GCC} thrcancel3.c -lpthread -o thrcancel3 ${ECHO}thrcancel3.c

clean:
	${RM} pthread_once thrcancel3 thrcancel2 thrcancel1 *~
