include ../Makefile.inc

P=fork/

all : frk1 frk2 frk3 frk4 frk5 frk6 frk7 frk8 frk9 frk10
	${GCC} frkas1.c -o frkas1 ${ECHO}frkas1.c
	${GCC} frkas.c -o frkas	${ECHO}frkas.c
	${GCC} frkfd.c -o frkfd ${ECHO}frkfd.c
	${GCC} sigchld1.c -o sigchld1 ${ECHO}sigchld1.c
	${GCC} sigchld.c -o sigchld ${ECHO}sigchld.c
	${GCC} frk1_ex.c -o frk1_ex ${ECHO}frk1_ex.c

frk1: frk1.c
	${GCC} frk1.c -o frk1  ${ECHO}frk1.c

frk2: frk2.c
	${GCC} frk2.c -o frk2 ${ECHO}frk2.c

frk3: frk3.c
	${GCC} frk3.c -o frk3 ${ECHO}frk3.c

frk4: frk4.c
	${GCC} frk4.c -o frk4 ${ECHO}frk4.c

frk5: frk5.c
	${GCC} frk5.c -o frk5 ${ECHO}frk5.c

frk6: frk6.c
	${GCC} frk6.c -o frk6 ${ECHO}frk6.c

frk7: frk7.c
	${GCC} frk7.c -o frk7 ${ECHO}frk7.c

frk8: frk8.c
	${GCC} frk8.c -o frk8 ${ECHO}frk8.c

frk9: frk9.c
	${GCC} frk9.c -o frk9 ${ECHO}frk9.c

frk10: frk10.c
	${GCC} frk10.c -o frk10 ${ECHO}frk10.c

clean:
	${RM} frk1 frk2 frk3 frk4 frk5 frk6 frk7 frk8 frk9 frk10 *.c~ \
	 frkas1 frkas frkfd sigchld sigchld1
