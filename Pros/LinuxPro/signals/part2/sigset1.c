#include <stdio.h>
#include <signal.h>

void sighand(int no)
{
	printf("\n %s: \n",__func__);
	printf(" I am in sighandler %d \n", no);
}

int main()
{
	sigset_t s_set;
	signal(62, sighand);
	signal(4, sighand);

	printf("pid %d\n", getpid());
	sigemptyset(&s_set);
	sigaddset(&s_set, 62);
	perror("sig1");

	sigaddset(&s_set, 4);
	perror("sig4");

	sigprocmask(SIG_BLOCK | SIG_SETMASK, &s_set, NULL);
	perror("sigmask");
	printf(" Send me signal one and see the effect now \n");
	getchar();

	sigprocmask(SIG_UNBLOCK, &s_set, NULL);
	printf(" Now signals are unblocked \n");
	while (1) ;
	return 0;
}
