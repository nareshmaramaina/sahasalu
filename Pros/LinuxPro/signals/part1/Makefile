include ../../Makefile.inc

P=signals/part1/

all:	
	${GCC} ignorepend.c -o ignorepend ${ECHO}ignorepend.c
	${GCC} oldact.c -o oldact	${ECHO}oldact.c
	${GCC} sigabort.c -o sigabort ${ECHO}sigabort.c
	${GCC} sigaction.c -o sigaction ${ECHO}sigaction.c
	${GCC} sigalarm1.c -o sigalarm1 ${ECHO}sigalarm1.c
	${GCC} sigalarm.c -o sigalarm ${ECHO}sigalarm.c
	${GCC} sigaltstack.c -o sigaltstack ${ECHO}sigaltstack.c
	${GCC} sigblock.c -o sigblock ${ECHO}sigblock.c
	${GCC} sigdefer.c -o sigdefer ${ECHO}sigdefer.c
	${GCC} sigign.c -o sigign ${ECHO}sigign.c
	${GCC} siginfo.c -o siginfo ${ECHO}siginfo.c
	${GCC} sigintr.c -o sigintr ${ECHO}sigintr.c
	${GCC} sigrestart.c -o sigrestart ${ECHO}sigrestart.c
	${GCC} sigwait2.c -o sigwait2 ${ECHO}sigwait2.c
	${GCC} sigwait.c -o sigwait ${ECHO}sigwait.c
	${GCC} test.c -o test ${ECHO}test.c
clean : 
	${RM} *~ ignorepend oldact sigabort sigaction sigalarm sigalarm1 sigaltstack sigblock sigdefer \
	sigign sigintr siginfo sigrestart sigwait sigwait2 test myfifo

