include ../../Makefile.inc
DIRS= part1  part2  


P=ipc/mqs/

all:	
	${GCC} test.c -o test ${ECHO}test.c
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done
clean : 
	${RM} test abc *~
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done

