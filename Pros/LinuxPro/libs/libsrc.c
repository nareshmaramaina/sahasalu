# include <stdio.h>

void test()
{
	printf("\n%s: \n",__func__);	
	printf("library test routine invoked\n");
}

int _init()
{
	printf("\n%s: \n",__func__);
	printf("in library init routine\n");
	return 0;
}

int _fini()
{
	printf("\n%s: \n",__func__);
	printf("in library fini routine\n");
	return 0;
}
