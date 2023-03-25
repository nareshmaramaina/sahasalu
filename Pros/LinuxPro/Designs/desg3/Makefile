include ../../Makefile.inc

P=Desings/desg3/

all: sos
	${GCC} config.c ui.c viml.c -o App -ldl ${ECHO}config.c ui.c viml.c
sos:
	${GCC} -c -fPIC gifhandler.c tifhandler.c jpghandler.c bmphandler.c 			\
	&& echo "  OBJ $Pgifhandler.o"								\
	&& echo "  OBJ $Ptifhandler.o"								\
	&& echo "  OBJ $Pjpghandler.o"								\
	&& echo "  OBJ $Pbmphandler.o"								
	${GCC} -shared -nostdlib gifhandler.o -o gifhand.so					\
	&& echo "  LIB $Pgifhand.so"								
	${GCC} -shared -nostdlib tifhandler.o -o tifhand.so					\
	&& echo "  LIB $Ptifhand.so"								
	${GCC} -shared -nostdlib jpghandler.o -o jpghand.so					\
	&& echo "  LIB $Pjpghand.so"								
	${GCC} -shared -nostdlib bmphandler.o -o bmphand.so					\
	&& echo "  LIB $Pbmphand.so"								
	

clean:
	rm -rf *App *.so *.o
