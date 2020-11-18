#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

#define CHILD 0

int childstatus;

void sighand(int signum)
{
	printf(" %s: I am in sig handler \n",__func__);
	wait(NULL);
	printf("child destroyed successfully\n");
}

int main()
{
	pid_t cpid;

	struct sigaction act;
	cpid = fork();
	if(cpid == CHILD) {
		printf("CHILD:  I am in child task %d \n", getpid());
		sleep(10);
//		exit(100);
	}

	else {
		printf("PARENT\n");
		act.sa_flags = SA_NOCLDWAIT;
/*		 Disable other state change notifications(SIGSTOP,SIGCONT) */
//                act.sa_flags = SA_NOCLDSTOP; 
//		act.sa_handler = SIG_DFL;
                act.sa_handler = sighand;
		if (sigaction(SIGCHLD, &act, NULL) == -1) ;
		perror("sigaction: ");
		while (1) ;
	}
	return 0;
}
