include ../../Makefile.inc
P=net/netp2/
all:
	${GCC} cli.c -o cli ${ECHO}cli.c
	${GCC} cli3.c -o cli3 ${ECHO}cli3.c
	${GCC} srv1.c -o srv1 ${ECHO}srv1.c
	${GCC} srv2.c -o srv2 ${ECHO}srv2.c
	${GCC} srv3.c -o srv3 ${ECHO}srv3.c
	${GCC} srv4.c -o srv4 -lpthread ${ECHO}srv4.c
	${GCC} srv5.c -o srv5 -lpthread ${ECHO}srv5.c

clean:
	${RM} *~ cli cli3 srv1 srv2 srv3 a.out srv4 srv5
