#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#define CHILD 0

int global;

int main()
{
	pid_t pid;
	int childstatus;
	global = 1;
	pid = fork();
	if (pid == CHILD) {
		printf("CHILD:  in child global %d\n", global);
		global = 10;
		printf("CHILD:  in child global %d\n", global);
		exit(1);
	}
	// parent
	else {
		wait(&childstatus);
		printf("PARENT: in parent global %d\n", global);
	}
	return 0;
}
