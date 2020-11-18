include ../Makefile.inc

P=sched/

all:	
	${GCC} affinity.c -o affinity ${ECHO}affinity.c
	${GCC} deamon.c -o deamon ${ECHO}deamon.c
	${GCC} priority1.c -o priority1 ${ECHO}priority1.c
	${GCC} priority.c -o priority ${ECHO}priority.c
	${GCC} sched_param.c -o sched_param ${ECHO}sched_param.c
	${GCC} sched_scheduler.c -o sched_scheduler ${ECHO}sched_scheduler.c
clean : 
	${RM} *~ affinity deamon priority1 priority sched_param sched_scheduler

