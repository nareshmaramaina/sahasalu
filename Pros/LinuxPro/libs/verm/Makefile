include ../../Makefile.inc

P=libs/verm/

all:
	${GCC} -c -fPIC lib.c  && echo -n "  OBJ $P" && echo "lib.o"
	${GCC} -shared lib.o -o libxyz.so && echo -n "  LIB $P" && echo "libxyz.so"
	${GCC} test.c ./libxyz.so -o test ${ECHO}test.c
	@#${GCC} test.c -L. -lxyz -o test ${ECHO}test.c
	
clean:
	${RM} *.so libtest *.a test *~
