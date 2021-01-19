#include<stdio.h>
int main()
{
	volatile register int i=1;
	int j=0;
	printf(" %d\n",i);
	//	printf("%p %p\n",i,&j);
	return 0;
}
