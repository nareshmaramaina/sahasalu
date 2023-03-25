# include <stdio.h>

void common2()
{
	printf("\n%s: \n",__func__);
	printf("libb common2\n");
}
void libb()
{
	printf("\n%s: \n",__func__);
	common2();
}
