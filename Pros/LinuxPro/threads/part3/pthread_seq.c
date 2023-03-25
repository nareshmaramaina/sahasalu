#include <pthread.h>
#include "pthread_seq.h"

int pthread_seq_init_np(pthread_seq_t * lck)
{
	int ret;
	printf("\n %s: \n",__func__);
	pthread_spin_init(&lck->spin, PTHREAD_PROCESS_PRIVATE);
	lck->writecount = 0;
	return 0;
}

int pthread_seq_rdlock_np(pthread_seq_t * lck)
{
	printf("\n %s: \n",__func__);
	return lck->writecount;
}

int pthread_seq_rdunlock_np(pthread_seq_t * lck)
{
	printf("\n %s: \n",__func__);
	return lck->writecount;
}

int pthread_seq_wrlock_np(pthread_seq_t * lck)
{
	int ret;
	printf("\n %s: \n",__func__);
	ret = pthread_spin_lock(&lck->spin);
	return ret;
}

int pthread_seq_wrunlock_np(pthread_seq_t * lck)
{
	int ret;
	printf("\n %s: \n",__func__);
	__sync_add_and_fetch(&lck->writecount, 1);
	ret = pthread_spin_unlock(&lck->spin);
	return ret;
}
