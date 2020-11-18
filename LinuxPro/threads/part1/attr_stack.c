#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

void read_stack_attrib(pthread_attr_t *attr)
{
	printf("\n %s: \n",__func__);
        void *getStkAddr;
        size_t getStkSize;

        pthread_attr_getstack(attr, &getStkAddr,&getStkSize);
        printf("t_routine: Current Stack starts @ %d and is of size  = %ld \n",getStkAddr,getStkSize);
}


void * t_routine (void *p)
{
   pthread_attr_t attr;
	printf("\n %s: \n",__func__);
   pthread_getattr_np(pthread_self(), &attr);
   read_stack_attrib(&attr);
   pthread_exit(NULL);	
}


int main()
{
        pthread_t tcb;
        pthread_attr_t attr;

        size_t stacksize =  16900; // in Bytes minimum 16 KB
        void *stackaddr;
	int align = getpagesize();

	/* allocate memory with page alignment */
	posix_memalign(&stackaddr, align, stacksize);

	printf("Main routine: Stack allocated @ %d address \n", stackaddr);

        pthread_attr_init(&attr);

	pthread_attr_setstack(&attr, stackaddr, stacksize);

        pthread_create(&tcb, &attr, t_routine, NULL);

	pthread_exit(NULL);
}
