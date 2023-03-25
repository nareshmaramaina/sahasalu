#include <stdio.h>
#include <malloc.h>

void malloc_status(struct mallinfo status)
{
	printf("\n total size of memory allocated with sbrk by malloc : %6d",
	       status.arena);
	printf("\n number of free chunks                        	: %10d",
	       status.ordblks);
	printf("\n number of mmapped regions                    	: %10d",
	       status.hblks);
	printf("\n space in mmapped regions                     	: %10d",
	       status.hblkhd);
	printf("\n total allocated space                        	: %10d",
	       status.uordblks);
	printf("\n total free space                             	: %10d",
	       status.fordblks);
	printf
	    ("\n top-most, releasable (via malloc_trim) space 	: %10d\n",
	     status.keepcost);
}

void * __attribute__((malloc)) alloc_block(int size)
{
        void *p;
        if(size<0) 
                return NULL;

        p = malloc(size);
        return p;
}

int main()
{
	struct mallinfo status;
	void *p1, *p2;

	status = mallinfo();
	malloc_status(status);

	/* Allocate small block */
	printf("\nAllocating 1000 bytes\n");
	p1 = alloc_block(1000);
	status = mallinfo();
	malloc_status(status);
	getchar();

	printf("\nFree 1000 bytes\n");
	free(p1);
	status = mallinfo();
	malloc_status(status);
	getchar();
	
	/* Allocate huge block */
	printf("\nAllocating 128KB\n");
	p2 = alloc_block(140*1024);	/* 140 KB */
	status = mallinfo();
	malloc_status(status);
	getchar();

	printf("\nFree 140KB\n");
	free(p2);
	status = mallinfo();
	malloc_status(status);

	return 0;
}
