
					/* get and set scheduling policies & priority of a thread */


#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;

void *lowprio(void *null)
{
	int i;
	printf("\n %s: \n",__func__);
	printf("LOWPRIO : contending for mutex lock \n");
	if(pthread_mutex_lock(&mutex)==0)
	{
	        printf("LOWPRIO : lock acquired\n");
		printf("LOWPRIO : executing critical op ......\n");
		/*  Busy loop for delay  */
		while(i<40000000)
			i++;
		/* end of busy loop*/
		printf("LOWPRIO : Done\n");
		printf("LOWPRIO : Releasing mutex \n");
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}



void * highprio(void *null)
{
	printf("HIGHPRIO : contending for mutex lock \n");
	if(pthread_mutex_lock(&mutex)==0)
	{
		printf("HIGHPRIO : lock acquired \n");
		printf("HIGHPRIO : executing critical op ......\n");
		printf("HIGHPRIO : Done\n");
		printf("HIGHPRIO : Releasing mutex \n");
	}
	pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
}

void * medprio(void *null)
{
	int i= 1;
	printf("MEDPRIO : acquired cpu \n");
	while(i<100){
		printf("MEDPRIO : running\n");
		i++;
	}
}



int main (int argc, char *argv[])
{
	pthread_mutexattr_t attrmutex;

	int inherit,policy,priority,rc;
        struct sched_param param;

	pthread_t tcb1,tcb2,tcb3;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
/* --------------------------------------------------------------------------- */
	pthread_mutexattr_init(&attrmutex);
	pthread_mutexattr_setprotocol(&attrmutex,PTHREAD_PRIO_INHERIT);
	pthread_mutex_init(&mutex,&attrmutex);
/* --------------------------------------------------------------------------- */

	
	// Sets inheritsched attribute 
	pthread_attr_setinheritsched(&attr,PTHREAD_EXPLICIT_SCHED);
	param.sched_priority=1;
	pthread_attr_setschedpolicy(&attr, SCHED_RR);
	pthread_attr_setschedparam(&attr, &param);
	
	
	pthread_create(&tcb1, &attr, lowprio, NULL);

	param.sched_priority=60;
	pthread_attr_setschedpolicy(&attr,SCHED_RR);
	pthread_attr_setschedparam(&attr,&param);

	pthread_create(&tcb2, &attr, highprio, NULL);

	param.sched_priority=50;
        pthread_attr_setschedpolicy(&attr,SCHED_RR);
        pthread_attr_setschedparam(&attr,&param);
	
	pthread_create(&tcb3, &attr, medprio, NULL);
	
	
	pthread_attr_destroy(&attr);

	pthread_exit(NULL);

}


