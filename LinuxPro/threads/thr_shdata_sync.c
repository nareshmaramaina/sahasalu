#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct G {
	int a;
	int b;
};

struct G obj; /* Global data structure */

int lock=0;  /* atomic counter */

static void * threadFunc1(void *arg) /* Thread 1 */
{
    while(lock!=0);
    printf("Thread1: accessing  shared data \n");
    __sync_fetch_and_add(&lock,1);		/* lock */
    obj.a=10;
    sleep(2);
    obj.b=20;
    __sync_fetch_and_sub(&lock,1);		/* unlock */
    return NULL;
}

static void * threadFunc2(void *arg)		/* Thread 2 */
{
    sleep(1);
    while(lock!=0);				/* lock */
    printf("Thread2: is accessing shared data \n");
    __sync_fetch_and_add(&lock,1);
    printf("obj.a = %d\n",obj.a);
    printf("obj.b = %d\n",obj.b);
    __sync_fetch_and_sub(&lock,1);		/* unlock */
    return NULL;
}

int main()
{
    pthread_t t1, t2;
    int ret;

    ret = pthread_create(&t1, NULL, threadFunc1, NULL);
    if (ret != 0)
        perror("Pthread Create :   ");

    ret = pthread_create(&t2, NULL, threadFunc2, NULL);
    if (ret != 0)
	perror("Pthread Create:    ");

    ret = pthread_join(t1, NULL);
    if (ret != 0)
	perror("Pthread Join:     ");

    ret = pthread_join(t2, NULL);
    if (ret != 0)
	perror("Pthreaf Join :    ");

    return EXIT_SUCCESS;
}
