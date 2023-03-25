include ../../Makefile.inc

P=threads/part1/
all:
	${GCC} attr_sched1.c -lpthread -o attr_sched1 ${ECHO}attr_sched1.c
	${GCC} attr_sched.c -lpthread -o attr_sched ${ECHO}attr_sched.c
	${GCC} attr_stack.c -lpthread -o attr_stack ${ECHO}attr_stack.c
	${GCC} defattrtib.c -lpthread -o defattrtib ${ECHO}defattrtib.c
	${GCC} detached_attrib.c -lpthread -o detached_attrib ${ECHO}detached_attrib.c
	${GCC} dyn_detach.c -lpthread -o dyn_detach ${ECHO}dyn_detach.c
	${GCC} dyn_join.c -lpthread -o dyn_join ${ECHO}dyn_join.c
	${GCC} ex2.c -lpthread -o ex2 ${ECHO}ex2.c
	${GCC} simple_thread1.c -lpthread -o simple_thread1 ${ECHO}simple_thread1.c
	${GCC} simple_thread.c -lpthread -o simple_thread ${ECHO}simple_thread.c

clean:
	${RM} *~ attr_stack attr_sched attr_sched1 defattrtib detached_attrib dyn_join dyn_detach  \
	ex2 simple_thread simple_thread1
