#include<stdio.h>

void func(int x,float y)
{
	printf("\n %s: \n",__func__);
	int i=11;
	printf("\n i = : %d ",i);
	i++;
	printf("\n i = : %d",i);
	i++;
	printf("\n i = : %d",i);
	i++;
	printf("\n i = : %d",i);
	i++;
	printf("\n i = : %d",i);
}

int main()
{
	printf("\n %s: \n",__func__);
	int x=100;
	func(100,20.6);
	printf("\n x = : %d\n",x);
	return 0;
}

