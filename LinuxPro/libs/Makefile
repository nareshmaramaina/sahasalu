include ../Makefile.inc

P=libs/

DIRS=sym  verm



all:
	${GCC} -c -fPIC one.c && echo -n "  OBJ $P" && echo "one.o"
	${GCC} -c -fPIC two.c && echo -n "  OBJ $P" && echo "two.o"
	${GCC} -c -fPIC libsrc.c && echo -n "  OBJ $P" && echo "libsrc.o"
	${GCC} -shared one.o -o libone.so && echo -n "  LIB $P" && echo "libone.so"
	${GCC} -shared two.o -o libtwo.so && echo -n "  LIB $P" && echo "libtwo.so"
	${GCC} -shared -nostdlib libsrc.o -o libsrc.so && echo -n "  LIB $P" && echo "libsrc.so"
	${GCC} libtest.c ./libone.so -o libtest ${ECHO}libtest.c
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}) ; done
	
clean:
	${RM} *.so libtest *.a 
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
