#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

#define CHILD 0

int childstatus;
pid_t cpid, cpid1;

/* signal handler to handle SIGCHLD event */
void sighand(int signum)
{
	printf(" I am in sig handler \n");
	waitpid(cpid1, NULL,0);
	/* wait()
	   {
	   step 1: block caller until child terminates
	   step 2: instruct kernel's process manager to destroy defunc child
	   step 3: return child's exit status to caller
	   } */
}

int main()
{
	cpid = fork();
	if (cpid == CHILD) {
		printf(" I am in child 1 my pid is %d \n", getpid());
		sleep(10);
		exit(100);
	} else {
//              wait(NULL);
		cpid1 = fork();
		if (cpid1 == CHILD) {
			printf("In child 2 my pid is %d", getpid());
			sleep(10);
			exit(0);
		} else {
			/* register signal handler with process manager */
			signal(SIGCHLD, sighand);
			waitpid(cpid, NULL, 0);
			while (1) {
				printf(" in loop \n");
				sleep(3);
			}
		}
	}
	return 0;
}
