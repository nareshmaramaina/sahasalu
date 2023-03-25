#include <stdio.h>
#include <malloc.h>	

main ()
{
	void *p;
	malloc_stats();	
	p = malloc(1);
	printf("\n number of usable allocated bytes associated with allocated chunk : %d \n",malloc_usable_size(p));
	free(p);
	malloc_stats();	
	printf("\n number of usable allocated bytes associated with allocated chunk : %d \n",malloc_usable_size(p));
	p = malloc(180);
	malloc_stats();	
	printf("\n number of usable allocated bytes associated with allocated chunk : %d \n",malloc_usable_size(p));
	free(p);
	malloc_stats();	
	printf("\n number of usable allocated bytes associated with allocated chunk : %d \n",malloc_usable_size(p));

}


