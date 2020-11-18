#include <linux/module.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/kmod.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/io.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include "lcdkp_io.h"

#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/sched.h>        /* for jiffies */
#include <asm/uaccess.h>        /*  for copy_from_user    */
#include <mach/hardware.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/imx_adc.h>


#define MAJORNO            231
#define NAME            "lcd_kp_cntrl"


extern volatile int backlight_timeout ;
extern volatile int key_buzzer_onoff_flag ;
extern volatile int touch_buzzer_onoff_flag ;

struct drv_batsense{
        int batsense_val;
}drv_battery;



static struct timer_list my_timer;

static struct work_struct user_mode_func;
static int lcd_kp_open(struct inode *, struct file *);
static int lcd_kp_release(struct inode *, struct file *);
static ssize_t lcd_kp_read(struct file *, char *, size_t , loff_t * );
static long lcd_kp_ioctl(struct file *, unsigned int , unsigned long );

void helper_function(void);
void setup_int(void);
void setup_exit(void);



static void my_timer_function (unsigned long ptr)
{
//	printk("In timer function\n");
	schedule_work(&user_mode_func);
	my_timer.expires = jiffies + 10;    
        add_timer (&my_timer);
	

}


void  helper_function  (void)
{
//	struct subprocess_info *info;
	
//	printk("In helper function\n");

        char *argv[] = { "/usr/bin/rgb" ,"0",NULL };
        char *argv1[] = { "/usr/bin/low_battery" ,"0",NULL };
        static char * envp[] = { "HOME=/","TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL };
        call_usermodehelper("/usr/bin/rgb", argv, envp,1 ? 1 : 1);
        call_usermodehelper("/usr/bin/low_battery", argv1, envp,1 ? 1 : 1);

}

struct file_operations lcd_kp_fops={
        .owner =THIS_MODULE,
        .open =lcd_kp_open,
        .read =lcd_kp_read,
        .unlocked_ioctl =lcd_kp_ioctl,
        .release =lcd_kp_release,
};

static int lcd_kp_open(struct inode *inode, struct file *filp)
{
        return 0;
}

static int lcd_kp_release(struct inode *inode, struct file *filp)
{
        return 0;
}

static ssize_t lcd_kp_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
        return -EINVAL;
}



static long lcd_kp_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	switch(cmd){
		case BUZZER:
			if((unsigned int)arg == 1){
				gpio_set_value(MX6_BRD_KP_BUZZER,1);
			}
			else{
				gpio_set_value(MX6_BRD_KP_BUZZER,0);
			}
				break;
		case KEY_BUZZER:
			if((unsigned int)arg == 1){
				key_buzzer_onoff_flag = 1;
			}
			else
				key_buzzer_onoff_flag =0;

				break;
		case TOUCH_BUZZER:
			if((unsigned int)arg == 1){
				touch_buzzer_onoff_flag = 1;
			}
			else
				touch_buzzer_onoff_flag =0;

				break;
		case LCD_BKL:
			if((unsigned int)arg == 0){
			//	printk("LCD_BKL ===========arg=%d\n",arg);
				gpio_set_value(MX6_BRD_LCD_BACKLIGHT,0);
				gpio_set_value(MX6_BRD_KP_BACKLIGHT,0);
			}
			else{
			//	printk("LCD_BKL ===========arg=%d\n",arg);
				gpio_set_value(MX6_BRD_LCD_BACKLIGHT,1);
				gpio_set_value(MX6_BRD_KP_BACKLIGHT,1);
			}
                       	 break;
			
                case LCD_BKL_TIMEOUT:
				backlight_timeout = (unsigned int)arg;
				udelay(10);	
                       	 break;
		
		case BATTER_SENSE:
			drv_battery.batsense_val = gpio_get_value(MX6_BRD_BAT_SENSE);
			if (copy_to_user ((struct drv_batsense*)arg,&drv_battery, sizeof(struct drv_batsense)))
                                return -EFAULT ;

			break;			
		default :
                        printk("Invalid Ioctl command\n");
                        break;
	}
	
	return 0;
}

static __init int usermode_init(void)
{
//	printk("In init Function\n");
	int result = 0;
        result=register_chrdev(MAJORNO, NAME,&lcd_kp_fops);
        if(result<0)
                return result;
        setup_init();

	init_timer (&my_timer);     /* intialize */
        my_timer.function = my_timer_function;
        my_timer.expires = jiffies + 1;    /* 10 seconds delay */
        add_timer (&my_timer);
	INIT_WORK(&user_mode_func,helper_function);

	return 0;
}

static __exit void  usermode_exit(void)
{
	del_timer_sync(&my_timer);
	setup_exit();
	unregister_chrdev(MAJORNO,NAME);
}

module_init(usermode_init);
module_exit(usermode_exit);

MODULE_AUTHOR("Malleswari");
MODULE_DESCRIPTION("LCD-keypad IO controller for IMX6SL");
MODULE_LICENSE("GPL");
