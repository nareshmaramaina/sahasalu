include ../Makefile.inc

P=threads/


DIRS=part1  part2  part3  part4

all:
	${GCC} procon.c -lpthread -o procon ${ECHO}procon.c
	${GCC} proconsyn.c -lpthread -o proconsyn ${ECHO}proconsyn.c
	${GCC} prod_condvar1.c -lpthread -o prod_condvar1 ${ECHO}prod_condvar1.c
	${GCC} thr_shdata_abmon.c -lpthread -o thr_shdata_abmon ${ECHO}thr_shdata_abmon.c
	${GCC} thr_shdata.c -lpthread -o thr_shdata ${ECHO}thr_shdata.c
	${GCC} thr_shdata_sync.c -lpthread -o thr_shdata_sync ${ECHO}thr_shdata_sync.c
	${GCC} thr_shdata_syncmtx.c -lpthread -o thr_shdata_syncmtx ${ECHO}thr_shdata_syncmtx.c
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done

clean:
	${RM} *~ procon proconsyn prod_condvar1 thr_shdata_syncmtx thr_shdata_sync thr_shdata thr_shdata_abmon
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
