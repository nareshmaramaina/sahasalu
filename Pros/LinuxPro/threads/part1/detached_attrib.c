
/* detached_attrib.c

   An example of the use of POSIX thread attributes (pthread_attr_t):
   creating a detached thread.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


#define DEATH(mess) { perror(mess); exit(errno); }

static void * threadFunc(void *x)
{
	printf("\n %s: \n",__func__);    
	return x;
}

int main()
{
    pthread_t thr;
    pthread_attr_t attr;
    int ret;

    /* Assigns default values */
    ret = pthread_attr_init(&attr);   
    if (ret!= 0)
       perror("pthread_attr_init");

    /* Assign detached state to PTHREAD_CREATE_DECTACHED */
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (ret != 0)
        perror("pthread_attr_getdetachstate");

    ret = pthread_create(&thr, &attr, threadFunc, (void *) 1);
    if (ret != 0)
        DEATH ("pthread_create");

    ret = pthread_attr_destroy(&attr);    /* No longer needed */
    if (ret != 0)
        perror( "pthread_attr_destroy");

    ret = pthread_join(thr, NULL);
    if (ret != 0)
        perror("pthread_join failed as expected");

    pthread_exit(NULL);
}
