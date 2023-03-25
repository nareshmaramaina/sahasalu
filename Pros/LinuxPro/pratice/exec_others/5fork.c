#include<stdlib.h>
#include <unistd.h>
#include<stdio.h>
int main()
{
	int i;
	for(i=0;i<5;i++)
	{
		if(fork()==0)
			printf("chlid%d process\n",i);
else exit(0);
	}
	return 0;
}
