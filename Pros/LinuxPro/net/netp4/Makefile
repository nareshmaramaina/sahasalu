include ../../Makefile.inc

P=net/netp4/

all:
	${GCC} cli1.c -o cli1 ${ECHO}cli1.c
	${GCC} cli2.c -o cli2 ${ECHO}cli2.c
	${GCC} clitest.c -o clitest ${ECHO}clitest.c
	${GCC} cli31.c -o cli31 ${ECHO}cli31.c
	${GCC} srv1.c -o srv1 ${ECHO}srv1.c
	${GCC} srv2.c -o srv2 ${ECHO}srv2.c
	${GCC} srv3.c -o srv3 ${ECHO}srv3.c
	${GCC} srv.c -o srv ${ECHO}srv.c
clean:
	${RM} cli31 cli2 clitest srv1 srv2 srv3 srv cli1 a.out *~ 
