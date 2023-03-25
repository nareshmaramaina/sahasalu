include ../../Makefile.inc

P=threads/part3/
all:
	${GCC} barrier.c -lpthread -o barrier ${ECHO}barrier.c
	${GCC} prod_condvar2.c -lpthread -o prod_condvar2 ${ECHO}prod_condvar2.c
	${GCC} pthread_rwlock.c -lpthread -o pthread_rwlock ${ECHO}pthread_rwlock.c
	${GCC} pthread_spinlock.c -lpthread -o pthread_spinlock ${ECHO}pthread_spinlock.c
	${GCC} rw_wriprio.c pthread_seq.c -lpthread -o rw_wriprio ${ECHO}rw_wriprio.c

clean:
	${RM} *~ barrier prod_condvar2 pthread_spinlock pthread_seq pthread_rwlock rw_wriprio
