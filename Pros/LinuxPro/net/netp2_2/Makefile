include ../../Makefile.inc

P=net/netp2_2/

all:
	${GCC} cli1.c -o cli1 ${ECHO}cli1.c
	${GCC} cli2.c -o cli2 ${ECHO}cli2.c
	${GCC} srv1.c -o srv1 ${ECHO}cli3.c
	${GCC} srv3.c lib1.c -o srv3 ${ECHO}srv3.c
	
clean:
	${RM} cli1 cli2 srv1 srv3 a.out
