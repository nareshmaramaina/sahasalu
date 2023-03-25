#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#define CHILD 0

int main()
{
	pid_t cPid;
	int childstatus;
	int k = 10;

	cPid = fork();
	if (cPid == CHILD) {
		printf(" child: My pid = %d \n", getpid());
		printf(" end of child k = %d\n", k);
		k = 44;
		printf(" end of child k = %d\n", k);
		exit(100);
	} else {
		wait(&childstatus);
		printf("parent: end of parent k = %d\n", k);
		getchar();
	}
	return 0;
}

/* cPid = fork();
   if(cPid  == 0)
	code that runs in child
   else
	wait(NULL);
	code that runs in parent

wait(int *childstatus)
{
	step 1: suspend caller until child terminates
	step 2: read exit value of child when child's termination is reported
	step 3: instruct process manager to destroy child pcb that is in exit state
}
*/
