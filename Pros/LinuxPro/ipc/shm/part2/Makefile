include ../../../Makefile.inc

P=ipc/shm/part2/

DIRS=shmsync

all:	
	${GCC}  anon_mmap.c  -o anon_mmap ${ECHO}anon_mmap.c
	${GCC}  pshm_create.c -lrt -o pshm_create  ${ECHO}pshm_create.c
	${GCC}  pshm_read.c -lrt -o  pshm_read  ${ECHO}pshm_read.c
	${GCC}  pshm_unlink.c -lrt -o pshm_unlink ${ECHO}pshm_unlink.c
	${GCC}  pshm_write.c -lrt -o pshm_write  ${ECHO}pshm_write.c
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done
clean : 
	${RM} *~ anon_mmap pshm_write pshm_create pshm_create pshm_unlink pshm_read
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done

