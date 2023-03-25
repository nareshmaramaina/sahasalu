#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/signalfd.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void catcher(int sig)
{
	printf("\n %s: \n",__func__);
	printf("Signal catcher called for signal %d\n", sig);
}

void timestamp(char *str)
{
	time_t t;
	time(&t);
	printf("\n %s: \n",__func__);
	printf("The time %s is %s\n", str, ctime(&t));
}

int main(int argc, char *argv[])
{

	int result = 0;
	int sfd, j;
	ssize_t s;
	struct sigaction sigact;
	sigset_t waitset;
	struct signalfd_siginfo info;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigact.sa_handler = catcher;
	sigaction(SIGALRM, &sigact, NULL);

	sigemptyset(&waitset);
	sigaddset(&waitset, SIGALRM);

	sigprocmask(SIG_BLOCK, &waitset, NULL);

	sfd = signalfd(-1, &waitset, 0);
	if (sfd == -1)
		DEATH("signalfd");

	alarm(10);

	timestamp("before read() on signalfd");

	s = read(sfd, &info, sizeof(struct signalfd_siginfo));
	if (s != sizeof(struct signalfd_siginfo))
		DEATH("read");

	printf("%s: got signal %d \n", argv[0], info.ssi_signo);
	if (info.ssi_code == SI_QUEUE) {
		printf("; ssi_pid = %d; ", info.ssi_pid);
		printf("ssi_int = %d", info.ssi_int);
	}

	timestamp("after read() on signalfd");

	return (result);
}
