include ../../Makefile.inc

P=libs/sym/

all:
	${GCC} -c -fPIC lib.c -o liba.o && echo -n "  OBJ $P" && echo "liba.o"
	${GCC} -c -fPIC lib1.c -o libb.o && echo -n "  OBJ $P" && echo "libb.o"
	${GCC} -shared liba.o -o liba.so && echo -n "  LIB $P" && echo "liba.so"
	${GCC} -shared libb.o -o libb.so && echo -n "  LIB $P" && echo "libb.so"
	${GCC} dltest.c -ldl -o dltest ${ECHO}dltest.c
	
	@ar rcs libab.a liba.o libb.o && echo -n "  AR  $P" && echo "liba.o libb.o"
	$(GCC) test.c ./libab.a -o test
	
clean:
	${RM} *.so libtest *.a test dltest *~
