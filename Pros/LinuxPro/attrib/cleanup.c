#include<stdio.h>
#include<malloc.h>


#define clean_memory __attribute__((cleanup(cleanUp)))

void cleanUp(int **p)
{
	printf("\n %s: %p \n",__func__,*p);
	free(*p);
}
void test(int size)
{
	
        int *p clean_memory ;
	int i=0;
	p = malloc(size);

	printf("\n %s: %p \n",__func__,p);
}


int main()
{
	test(100);
	return 0;	
}
