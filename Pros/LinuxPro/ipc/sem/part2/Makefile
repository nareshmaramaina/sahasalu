include ../../../Makefile.inc

P=ipc/sem/part2/

all:	
	${GCC} psem_getvalue.c -lpthread -o psem_getvalue ${ECHO}psem_getvalue.c
	${GCC} psem_timedwait.c  -lpthread -o psem_timedwait ${ECHO}psem_timedwait.c
	${GCC} psem_trywait.c  -lpthread -o psem_trywait ${ECHO}psem_trywait.c
	${GCC} psem_unlink.c  -lpthread -o psem_unlink ${ECHO}psem_unlink.c
	${GCC} psem_wait.c  -lpthread -o psem_wait ${ECHO}psem_wait.c
	${GCC} semcreate.c  -lpthread -o semcreate ${ECHO}semcreate.c
	${GCC} sempost.c  -lpthread -o sempost ${ECHO}sempost.c
	${GCC} thread_incr_psem.c  -lpthread -o thread_incr_psem ${ECHO}thread_incr_psem.c
clean : 
	${RM} psem_getvalue psem_timedwait psem_trywait psem_unlink psem_wait sempost semcreate thread_incr_psem

