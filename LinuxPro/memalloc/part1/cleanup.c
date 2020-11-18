#include<stdio.h>
#include<malloc.h>


void test(int size)
{
	
        int *p;
	int i=0;
	printf("\n %s: \n",__func__);
	p = malloc(size);
	printf("\n %p \n",p);
	printf("\n");
}


int main()
{
	printf("\n %s: \n",__func__);	
	test(100);
	return 0;	
}
