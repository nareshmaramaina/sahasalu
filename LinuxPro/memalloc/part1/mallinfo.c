#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <malloc.h>

#define SIZE 4096	

void malloc_status(struct mallinfo status)
{
	printf("\n %s: \n",__func__);
	printf("\n total size of memory allocated with sbrk by malloc : %6d",status.arena);
        printf("\n number of free chunks                        	: %10d",status.ordblks);
        printf("\n number of mmapped regions                    	: %10d",status.hblks);
        printf("\n space in mmapped regions                     	: %10d",status.hblkhd);
        printf("\n total allocated space                        	: %10d",status.uordblks);
        printf("\n total free space                             	: %10d",status.fordblks);
        printf("\n top-most, releasable (via malloc_trim) space 	: %10d\n",status.keepcost);
}

int main ()
{
	struct mallinfo status;
	void *ptr;
	
	printf("default heap status \n");
	status = mallinfo();
	malloc_status(status);
//	getchar();

	printf("status after 1 page dynamic allocation \n");
	ptr = malloc(SIZE);
	status = mallinfo();
	malloc_status(status);
//	getchar();

	printf("status after free call to first allocation\n");	
	free(ptr);
	status = mallinfo();
	malloc_status(status);
//	getchar();

	exit(EXIT_SUCCESS);
}


