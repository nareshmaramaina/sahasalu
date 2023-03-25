include ../../../Makefile.inc

P=ipc/mqs/part2/

all:	
	${GCC} mq_notify_sig.c -lrt -o mq_notify_sig ${ECHO}mq_notify_sig.c
	${GCC} mq_notify_sigwaitinfo.c -lrt -o mq_notify_sigwaitinfo ${ECHO}mq_notify_sigwaitinfo.c
	${GCC} mq_notify_thread.c -lrt -o mq_notify_thread ${ECHO}mq_notify_thread.c
	${GCC} msgq1.c -lrt -o msgq1 ${ECHO}msgq1.c
	${GCC} msgq2a.c -lrt -o msgq2a ${ECHO}msgq2a.c
	${GCC} msgq2b.c -lrt -o msgq2b ${ECHO}msgq2b.c
	${GCC} msg_unlink.c -lrt -o msg_unlink ${ECHO}msg_unlink.c
clean : 
	${RM} *~ mq_notify_sig mq_notify_thread mq_notify_sigwaitinfo msg2b msgq1 msgq2a msgq2b msg_unlink

