/*
 * =====================================================================================
 *
 *       Filename:  thread.c
 *
 *    Description:  thread
 *
 *        Version:  1.0
 *        Created:  Thursday 11 March 2021 11:24:50  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */
#include <linux/module.h>
#include <linux/moduleparam.h>
#include<linux/kthread.h>
#include<linux/delay.h>
//#include<linux/sched.h>
static int myint=0;
//static int flag=0;
static atomic_t flag=ATOMIC_INIT(0);
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
struct task_struct *thread,*thread1;
//module_param(flag,int,S_IRUSR|S_IWUSR);
//MODULE_PARM_DESC(flag,"Giving flag");
//
wait_queue_head_t wq;
//DECLARE_WAIT_QUEUE_HEAD(wq);
int thread2(void *data)
{

	int i=0;

	while( ! kthread_should_stop() )
	{
		if ( i == 5 )
		{
			i=0;
			atomic_set(&flag,myint);
		//	wake_up_interruptible(&wq);
			pr_info(" Thread is Running Waiting ... %d %d \n",flag,myint);
		}
		i++;
	}
	pr_info(" Iam Exiting \n");
	return 0;
}

int thread_fn(void *data)
{
	int i=0;

	while( ! kthread_should_stop() )
	{
		pr_info(" Thread is Running Waiting ... %d  \n",flag);
		wait_event_interruptible(wq,atomic_read(&flag));
		pr_info(" Released %d \n",flag);
		return 0;

	}
	pr_info(" Iam Exiting \n");
	return 0;
}

static int th_init(void)
{
	init_waitqueue_head(&wq);
	thread = kthread_run(thread_fn,NULL,"Mastan123");
	thread1 = kthread_run(thread2,NULL,"Katu");
	pr_info(" Init = %d \n",myint);
	return 0;
}

static void th_exit(void)
{
	kthread_stop(thread);
	kthread_stop(thread1);
	pr_info(" Exit %p\n",thread);
	return;
}
module_init(th_init);
module_exit(th_exit);
MODULE_LICENSE("GPL");
