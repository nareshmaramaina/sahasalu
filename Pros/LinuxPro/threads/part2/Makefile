include ../../Makefile.inc

P=threads/part2/
all:
	${GCC} consistent.c -lpthread -o consistent ${ECHO}consistent.c
	${GCC} errchk.c -lpthread -o errchk ${ECHO}errchk.c
	${GCC} prio.c -lpthread -o prio ${ECHO}prio.c
	${GCC} recur.c -lpthread -o recur ${ECHO}recur.c
	${GCC} thread_incr_atomic.c -lpthread -o thread_incr_atomic ${ECHO}thread_incr_atomic.c
	${GCC} thread_incr.c -lpthread -o thread_incr ${ECHO}thread_incr.c
	${GCC} thread_incr_deadlock.c -lpthread -o thread_incr_deadlock ${ECHO}thread_incr_deadlock.c
	${GCC} thread_incr_mtx.c -lpthread -o thread_incr_mtx ${ECHO}thread_incr_mtx.c

clean:
	${RM} *~ consistent errchk prio recur thread_incr_atomic thread_incr thread_incr_deadlock thread_incr_mtx
