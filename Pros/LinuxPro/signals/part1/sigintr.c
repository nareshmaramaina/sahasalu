#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighand(int signum)
{
	printf("\n %s: \n",__func__);
	printf("Interrupt signal rec'd \n");
}

int main()
{
	signal(SIGINT, sighand);
	while (1) {
		sleep(1);
		printf("in loop\n");
	}
	return 0;
}
