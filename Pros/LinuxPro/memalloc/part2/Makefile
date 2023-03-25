include ../../Makefile.inc

P=memalloc/part2/

all:	
	${GCC} CHKFREED.c -o CHKFREED ${ECHO}CHKFREED.c
	${GCC} nooverrun.c -o nooverrun ${ECHO}nooverrun.c
	${GCC} OVERRUN.c -o OVERRUN 	${ECHO}OVERRUN.c
	${GCC} underrun.c -o underrun ${ECHO}underrun.c
clean : 
	${RM} *~ CHKFREED nooverrun OVERRUN underrun 

