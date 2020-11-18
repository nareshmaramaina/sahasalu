include ../Makefile.inc

P=lib/
all:
	${GCC} -c -fPIC mylib.c && echo -n "  OBJ $P" && echo "mylibc.o"
	${GCC} -shared mylib.o -o libxyz.so && echo -n "  LIB $P" && echo "libxyz.so"
	${GCC} mandl.c -o run -ldl ${ECHO}mandl.c
	
clean:
	${RM} *.so run
