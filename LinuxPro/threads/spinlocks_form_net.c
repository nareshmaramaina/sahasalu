#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/time.h>

#define LOOPS 10000000

int idx = 0,i;
int cs1 = 0, cs2 = 0;

pthread_spinlock_t spinlock;
pthread_spinlock_t spinlock1;

pid_t gettid() { return syscall( __NR_gettid ); }

void *consumer(void *ptr) {

	pthread_spin_lock(&spinlock);
	i--;
	printf("Consumer TID %lu %d\n", (unsigned long)gettid(),spinlock);
	pthread_spin_unlock(&spinlock);
	pthread_spin_lock(&spinlock1);
	puts("hlo");
	i++;
	pthread_spin_unlock(&spinlock1);
	return NULL;
}

int main() {
	pthread_t thr1, thr2;

	pthread_spin_init(&spinlock, 0);

	// Creating the list content...
	// Measuring time before starting the threads...
	pthread_create(&thr1, NULL, consumer, (void*)1);
	pthread_create(&thr2, NULL, consumer, (void*)2);

	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);

	// Measuring time after threads finished...

	return 0;
}
