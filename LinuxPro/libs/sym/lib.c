# include <stdio.h>

void common1()
{
	printf("\n%s: \n",__func__);
	printf("liba common1\n");
}
void liba()
{
	printf("\n%s: \n",__func__);
	common1();
}
