include ../../Makefile.inc

P=memalloc/part1/

all:	
	${GCC} cleanup.c -o cleanup ${ECHO}cleanup.c
	${GCC} cleanup1.c -o cleanup1 ${ECHO}cleanup1.c
	${GCC} demo.c -o demo 	${ECHO}demo.c
	${GCC} find_system_break.c -o find_system_break ${ECHO}find_system_break.c
	${GCC} mallinfo.c -o mallinfo ${ECHO}mallinfo.c
	${GCC} malloc.c -o malloc ${ECHO}malloc.c
	${GCC} malloc_stats.c -o malloc_stats ${ECHO}malloc_stats.c
	${GCC} malloc_tuning.c -o malloc_tuning ${ECHO}malloc_tuning.c
	${GCC} malloc_usable_size.c -o malloc_usable_size ${ECHO}malloc_usable_size.c
	${GCC} memlock.c -o memlock ${ECHO}memlock.c
	${GCC} oom.c -o oom ${ECHO}oom.c
clean : 
	${RM} *~ cleanup cleanup1 demo find_system_break mallinfo malloc malloc_usable_size \
	malloc_tuning malloc_stats memlock oom

