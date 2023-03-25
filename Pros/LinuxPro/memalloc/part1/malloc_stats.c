#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 350

int main ()
{
	void *handle;

	printf("\n Before Malloc Call \n");
	malloc_stats();
//	getchar();
	
	printf("\n After Malloc Call \n");
	handle = malloc(SIZE);
	malloc_stats();

	/* let's print usable size */
	printf("\n usable size %d \n",malloc_usable_size(handle));
//	getchar();

	printf(" \n After free call \n");	
	free(handle);
	malloc_stats();
//	getchar();
	exit(EXIT_SUCCESS);
}


