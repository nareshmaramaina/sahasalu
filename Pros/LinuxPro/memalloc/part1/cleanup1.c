#include<stdio.h>
#include<malloc.h>


#define clean_memory __attribute__((cleanup(cleanUp)))

void cleanUp(int **p)
{
	printf("\n %s: \n",__func__);
	printf("\n %p \n",*p);
	free(*p);
}
void test(int size)
{
	printf("\n %s: \n",__func__);
        int *p clean_memory ;
	int i=0;
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
