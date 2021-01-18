#include <linux/module.h>
#include <linux/init.h>
//#include <linux/errno.h>
#include <linux/types.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/kmod.h>

static struct timer_list my_timer;
static struct work_struct user_mode_func;


static void my_timer_function (unsigned long ptr)
{
//	printk("In timer function\n");
	schedule_work(&user_mode_func);
	my_timer.expires = jiffies + 10;    /* 60 tics */
        add_timer (&my_timer);
	

}


void  helper_function  (void)
{
//	struct subprocess_info *info;
	
//	printk("In helper function\n");

        char *argv[] = { "/root/rgb" ,"0",NULL };
        static char * envp[] = { "HOME=/","TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL };
        call_usermodehelper("/root/rgb", argv, envp,1 ? 1 : 1);

}


static __init int myinit(void)
{
	printk("In init Function\n");
	init_timer (&my_timer);     /* intialize */
        my_timer.function = my_timer_function;
        my_timer.expires = jiffies + 1;    /* 10 seconds delay */
        add_timer (&my_timer);
	INIT_WORK(&user_mode_func,helper_function);

	return 0;
}

static __exit void  myexit(void)
{
	del_timer_sync(&my_timer);
}

module_init(myinit);
module_exit(myexit);

MODULE_AUTHOR("chandrakanth");
MODULE_DESCRIPTION("UserMode-Helper Test");
MODULE_LICENSE("GPL");
