#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void thread1_function(char);
void thread2_function(void);
void thread3_function(void);
int sharing=7;
	pthread_t thread1,thread2,thread3;
int main()
{
	void *ptr;
char ch='b';
	if(pthread_create(&thread1,NULL,(void*)thread1_function,ch)==0)
		printf("creation success\n");
pthread_join(thread1,ptr);
	if(pthread_create(&thread2,NULL,(void*)thread2_function,NULL)==0)
		printf("creation success\n");
pthread_join(thread2,NULL);
//if(pthread_cancel(thread3)==0)
//printf("cancellation success\n");
//else perror("error:");
	if(pthread_create(&thread3,NULL,(void*)thread3_function,NULL)==0)
		printf("creation success\n");
pthread_join(thread3,NULL);
printf("*********%s",(char*)ptr);
	pthread_exit("thanks you");
}
void thread1_function(char ch )
{
	printf("iam in thread1%c....%d\n",ch,++sharing);
//	sleep(2);
}
void thread2_function( )
{
	printf("iam in thread2%d\n",sharing++);
//	sleep(2);
}
void thread3_function( )
{
	printf("iam in thread3%d\n",++sharing);
//	sleep(2);
}
