/* simple_thread.c

   A simple POSIX threads example: create a thread, and then join with it.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define DEATH(mess) { perror(mess); exit(errno); }

typedef struct abc{
	int a;
	int b;
}ABC;
static void * threadFunc(void *arg)
{
    ABC *p = (ABC *) arg;
	printf("\n %s: \n",__func__);
    printf("%d", p->a);
    printf("%d", p->b);

   pthread_exit(NULL);
}

int main()
{
    pthread_t t1;
    void *res;
    int ret;
 
    ABC obj;
    obj.a = 10;
    obj.b = 20;
	
    ret = pthread_create(&t1, NULL, threadFunc, &obj);
    if (ret != 0)
        DEATH ("pthread_create");

    printf("Message from main()\n");

    ret = pthread_join(t1, NULL);
    if (ret != 0)
        perror( "pthread_join");

    printf("Thread returned %ld\n", (long) res);

    exit(EXIT_SUCCESS);
}
