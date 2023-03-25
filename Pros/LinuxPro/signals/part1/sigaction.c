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
	alarm(5);
//	sleep(7);
}

int main()
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));

	/* Install signal handlers */
	act.sa_handler = handler;
	if (sigaction(SIGALRM, &act, NULL) < 0)
		DEATH("sigaction");

	printf("Successfully installed signal handler\n");

	/* schedule alarm to be signalled after 5 seconds */
	alarm(5);

	/* Do something pointless, forever */
	for (;;) {
		printf("This is a pointless message.\n");
		sleep(1);
	}

	return 0;
}
