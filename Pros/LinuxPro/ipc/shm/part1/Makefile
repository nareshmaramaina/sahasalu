include ../../../Makefile.inc

P=ipc/shm/part1/

all:	
	${GCC}  mem1.c  -o mem1   ${ECHO}mem1.c
	${GCC}  mem2a.c -o mem2a  ${ECHO}mem2a.c
	${GCC}  mem2b.c -o mem2b  ${ECHO}mem2b.c
	${GCC}  mem4.c -o mem4    ${ECHO}mem4.c
	${GCC}  mem51.c -o mem51  ${ECHO}mem51.c
	${GCC}  meminfo.c -o meminfo  ${ECHO}meminfo.c
	${GCC}  memlock.c -o memlock  ${ECHO}memlock.c
#	${GCC}  svshm_xfr_reader.c -o svshm_xfr_reader  ${ECHO}svshm_xfr_reader.c
#	${GCC}  svshm_xfr_writer.c -o svshm_xfr_writer  ${ECHO}svshm_xfr_writer.c
clean : 
	${RM} *~ mem1 mem2a mem2b mem4 mem51 meminfo memlock svshm_xfr_writer svshm_xfr_reader

