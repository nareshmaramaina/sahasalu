include ../Makefile.inc

P=startup/
all:
	${GCC} -E app.c -o app.i && echo -n "  PRE " && echo "$P"app.c
	${GCC} -S app.i && echo -n "  ASM " && echo "$P"app.i
	${GCC} -c app.s && echo -n "  OBJ " && echo "$P"app.s
	${GCC} app.o && echo -n "  CC  " && echo "$P"app.o
	${GCC} -nostartfiles test.c -o test ${ECHO}test.c

clean:
	${RM} *.i *.s *.o app test *~
