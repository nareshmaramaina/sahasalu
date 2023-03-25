#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int z=1;
void *f(void *);
void *f1(void *);
void *f2(void *);
sem_t sem;
int main()
{
	pthread_t th1,th2,th3;
	sem_t sem;
	void *v;
	if(sem_init(&sem,0,1)==-1)
	{
		perror("sem_init");
		exit(0);
	}
	//printf("size of sem_t%d\n",sizeof(sem_t));
	//sem_post(&sem);
	/*if(sem_post(&sem)==-1)
	  {
	  perror("sem_post");
	  exit(0);
	  }*/
	pthread_create(&th1,NULL,f,NULL);
	pthread_create(&th2,NULL,f1,NULL);
	pthread_create(&th3,NULL,f2,NULL);
	pthread_join(th1,NULL);
	//printf("thread %d exited\n",*(int *)v); 
	pthread_join(th2,NULL);
	//printf("thread%d exited\n",*(int *)v); 
	pthread_join(th3,NULL);
	//printf("thread%d exited\n",*(int *)v); 
	return 0;
}
void *f(void *p)
{
	int i;
	char ch='a';
	int a=1;
printf("value in f=%d\n",++z);	
        sem_post(&sem);
printf("value in f=%d\n",--z);	
	sem_wait(&sem);
	for(i=0;i<5;i++)
	{
		printf("%c",ch);
		fflush(stdout);
		sleep(1);
		ch++;
	}
printf("value in f=%d\n",++z);	
	sem_post(&sem);
	//printf("\n");
	//pthread_exit(&a);
	//usleep(100);
}
void *f1(void *p)
{
	int i;
	int a=2;
	char ch='A';
	//sem_post(&sem);
printf("value in f1=%d\n",--z);	
	sem_wait(&sem);
	for(i=0;i<5;i++)
	{
		printf("%c",ch);
		fflush(stdout);
		sleep(1);
		ch++;
	}
printf("value in f1=%d\n",++z);	
	sem_post(&sem);
	//pthread_exit(&a);
	//printf("\n");
	//usleep(100);
}
void *f2(void *p)
{
	int i,a=3;
	char ch='1';
printf("value in f2=%d\n",--z);	
	sem_wait(&sem);
	for(i=0;i<5;i++)
	{
		printf("%c",ch);
		fflush(stdout);
		sleep(1);
		ch++;
	}
printf("value in f2=%d\n",++z);	
	sem_post(&sem);
	//pthread_exit(&a);
	//printf("\n");
	//usleep(100);
}
