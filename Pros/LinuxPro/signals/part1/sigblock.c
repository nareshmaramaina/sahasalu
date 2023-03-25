#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define DEATH(mess) { perror(mess); exit(errno); }

/* our signal handlers */

void handler(int what)
{
	printf("\n %s: \n",__func__);
	printf("We have received SIGALRM: Executing periodic work\n");
	sleep(5);
	printf(" done sleeping 2 seconds\n");
}

int main()
{
	struct sigaction act;
	sigset_t sigmask;
	int rc;

	memset(&act, 0, sizeof(act));

	rc = sigemptyset(&sigmask);
	printf("rc = %d from sigemptyset\n", rc);
	rc = sigaddset(&sigmask, SIGQUIT);
	rc = sigaddset(&sigmask, SIGTERM);
	printf("rc = %d from sigaddset\n", rc);

	/* Install signal handlers */
	act.sa_handler = handler;
	act.sa_mask = sigmask;	/* block SIGQUIT */

	if (sigaction(SIGINT, &act, NULL) < 0)
		DEATH("sigaction");

	/* Do something pointless, forever */
	for (;;) {
		printf("This is a pointless message.\n");
		sleep(1);
	}

	return 0;
}
