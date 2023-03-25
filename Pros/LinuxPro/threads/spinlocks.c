#include<stdio.h>
#include<pthread.h>
//       int pthread_spin_trylock(pthread_spinlock_t *lock);

int main()
{
	pthread_spinlock_t lock=0;

	printf("Starting Dude \n");
	pthread_spin_lock(&lock);

	printf("Starting Dude %d\n",lock);
	pthread_spin_unlock(&lock);
	printf("Ending Dude %d\n",lock);
	return 0;
}
