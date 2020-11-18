#include<stdio.h>
#include<sys/mman.h>
#include<sched.h>
#include<stdlib.h>
#include<fcntl.h>

#define STACK_SIZE 16000

int dosomething(void *arg)
{
	fflush(stdout);
	printf(" %s : In child process\n",__func__);
	getchar();
}

int main()
{
	void *child_stack;
	/*get memory for child stack */
	child_stack = malloc(STACK_SIZE);
	if (child_stack == NULL) {
		perror("\nError creating \n");
		exit(1);
	}

	/*create new child with clone */
	clone(dosomething, child_stack + STACK_SIZE, CLONE_VM | CLONE_FILES,
	      NULL);
	printf("\nIn Parent process\n");
	while(1);
	return 0; // should never reach here
}
