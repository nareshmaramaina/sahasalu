/* thread_incr.c

   This program employs two POSIX threads that manipulate the same global
   data structure, without using any synchronization method. As a consequence,
   updates are sometimes lost.

*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define EXIT_SUCCESS 0

struct G {
	int a;
	int b;
	pthread_mutex_t lock;
};

struct G obj;			/* shared data object */

static void *threadFunc1(void *arg)
{
	int ret;
	ret = obj_lock(&obj);
	obj.a = 10;
	sleep(2);
	obj.b = 20;
	ret = obj_unlock(&obj);
	return NULL;
}

static void *threadFunc2(void *arg)
{
	int ret;
	ret = obj_lock(&obj);
	sleep(1);
	printf("obj.a = %d\n", obj.a);
	printf("obj.b = %d\n", obj.b);
	ret = obj_unlock(&obj);
	return NULL;
}

int obj_lock(struct G *obj)
{
	int ret;
	ret = pthread_mutex_lock(&obj->lock);
	if (ret > 0)
		return ret;
	return ret;
}

int obj_unlock(struct G *obj)
{
	int ret;
	ret = pthread_mutex_unlock(&obj->lock);
	if (ret > 0)
		return ret;
	return ret;
}

int obj_init(struct G *obj)
{
	int ret;
	obj->a = 0;
	obj->b = 0;
	ret = pthread_mutex_init(&obj->lock, NULL);
	if (ret > 0)
		return -1;
	return 0;

}

int main()
{
	pthread_t t1, t2;
	int ret;

	ret = obj_init(&obj);
	if (ret != 0) {
		printf("obj init failed\n");
		exit(1);
	}

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

	exit(EXIT_SUCCESS);
}
