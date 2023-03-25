#include <stdio.h>

void f1()
{
	printf("\n%s: \n",__func__);
	printf("lib call f1()\n");
	printf("new change\n");
}

void f2()
{
	printf("\n%s: \n",__func__);
	printf("lib call f2()\n");
}
