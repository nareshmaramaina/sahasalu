include ../Makefile.inc

P=ioperm/
all:
	${GCC} getclk.c -o get ${ECHO}getclk.c
	${GCC} setclk.c -o set ${ECHO}setclk.c
	${GCC} rtc.c -o rtc ${ECHO}rtc.c
	${GCC} spek.c -o spek ${ECHO}spek.c

clean:
	${RM} get set rtc spek
