#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define CHILD 0

int main()
{
	pid_t childpid;
	childpid = fork();
//	printf(" Childpid value is %d\n ",childpid);
//	printf("hello fork %d\n", getpid());
	if (childpid == CHILD) {
		printf("child: My pid = %d and ppid = %d\n", getpid(),
		       getppid());
		sleep(10);
//                while (1) ;
	} else {
		printf("PARENT :pid = %d\n", getpid());
		while (1) ;
//                sleep(10);
	}


	return 0;
}

/*      
	childpid = fork();
	if (childPid == CHILD) 
		work to be executed in child
	else
		work to be executed in parent
*/





















