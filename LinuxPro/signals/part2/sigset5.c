#include <stdio.h>
#include <signal.h>

void check_blocked_sigs()
{
	printf("\n %s: \n",__func__);
	int i, res;
	sigset_t s;
	sigprocmask(SIG_BLOCK, NULL, &s);	//first param is not considered
	for (i = 1; i < 32; i++) {
		res = sigismember(&s, i);
		if (res)
			printf(" signal %d is blocked \n", i);
		else
			printf(" signal %d is not blocked \n", i);
	}
}

int main()
{
	sigset_t s_set;
	sigfillset(&s_set);
	sigprocmask(SIG_BLOCK | SIG_SETMASK, &s_set, NULL);
	check_blocked_sigs();
	return 0;
}
