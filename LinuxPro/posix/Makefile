include ../Makefile.inc

P=posix/

all:	
	${GCC} ansilimits.c -o ansilimits ${ECHO}ansilimits.c
	${GCC} PERR.c -o PERR	${ECHO}PERR.c
	${GCC} posixlimits.c -o posixlimits ${ECHO}posixlimits.c
	${GCC} posixopts.c -o posixopts ${ECHO}posixopts.c
	${GCC} POSIXVER.c -o POSIXVER ${ECHO}POSIXVER.c
	${GCC} PRL.c -o PRL ${ECHO}PRL.c
	${GCC} STDARGS.c -o STDARGS ${ECHO}STDARGS.c
clean : 
	${RM} *~ ansilimits PERR POSIXVER PRL posixlimits posixopts STDARGS

