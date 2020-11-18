#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/fs.h>		/* for register_chardev, file_operations  etc. */
#include <linux/init.h> 
#include <linux/mm.h>
#include <linux/sched.h>	/* for jiffies */
#include <asm/uaccess.h>	/*  for copy_from_user    */
#include <asm/io.h>		/* to access io memory */
#include <mach/hardware.h>
#include <mach/gpio.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/imx_adc.h>
#include <linux/kernel.h>
#include <linux/kthread.h>

#include <linux/interrupt.h>
#include <mach/hardware.h>
#include <mach/gpio.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/clk.h>


//#include"../arch/arm/plat-mxc/include/mach/iomux-mx6sl.h"
#include "/u03/BANDHAN/working/kernel/linux-3.0.35/arch/arm/plat-mxc/include/mach/iomux-mx6sl.h"
#include "ioc_hardware.h"

#define MAJORNO 235		/* major no for device */
#define NAME "ioc"

#define ADPT_BAT1                           0X01
#define BATT_BAT2                           0x02


struct drv_batsense{
        int batsense_val;
}drv_battery;

extern volatile int backlight_timeout ;
extern volatile int key_buzzer_onoff_flag ;
extern volatile int touch_buzzer_onoff_flag ;

static int cam_flag=0;
static  int lcd_bkl_flag=0;

//extern int AD7877_Read_batinfo(int,char *);
//static int get_power();
//static int get_battery();
volatile int flash_onflag=0;
unsigned long int  flash_timeout=0;
void poweroff_battery(void)
{
        static char * envp[] = { "HOME=/","TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL };
        char *argv[] = { "/sbin/battery" ,"0",NULL };
        call_usermodehelper("/sbin/battery", argv, envp,1 ? 1 : 1);

}

void  rgb_function  (void)
{
        char *argv[] = { "/usr/bin/rgb" ,"0",NULL };
        static char * envp[] = { "HOME=/","TERM=linux", "PATH=/sbin:/usr/sbin:/bin:/usr/bin", NULL };
        call_usermodehelper("/usr/bin/rgb", argv, envp,1 ? 1 : 1);

}

static int work_thread(void *arg);
static atomic_t data_present=ATOMIC_INIT(0);
DECLARE_WAIT_QUEUE_HEAD(wq);
static void gl11_timer_work  (unsigned long arg) ;

static struct timer_list gl11_timer ;

static int ioc_open(struct inode *, struct file *);
static int ioc_release(struct inode *, struct file *);

//static struct work_struct low_battery_poweroff_wq;
//static struct work_struct rgb_work_struct;


static int ioc_open(struct inode *, struct file *);
static int ioc_release(struct inode *, struct file *);
static ssize_t ioc_read(struct file *, char *, size_t, loff_t *);
static ssize_t ioc_write(struct file *, const char *, size_t, loff_t *);
static long ioc_ioctl(struct file *flip, unsigned int cmd, unsigned long arg);

int exit_flag=1;


//extern int touch_delay;
extern int touch_pnt_out;
extern char key_out_flag;
extern char touch_release_flag;
volatile int buz_counter=2;	//2

volatile int bkl_on=0;
volatile int bkl_off=0;
volatile int buzz_on_flg=1;
volatile int touch_buzz=1;


static const struct file_operations ioc_fops = {
	.owner = THIS_MODULE,
	.open = ioc_open,
	.read = ioc_read,
	.write = ioc_write,
	.unlocked_ioctl = ioc_ioctl,
	.release = ioc_release,
};


static int ioc_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int ioc_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t ioc_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
	return -EINVAL;
}

static ssize_t ioc_write(struct file *filp, const char *buff, size_t length, loff_t * off)
{
	return -EINVAL;
}

static long ioc_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{

//	printk("\ncmd.........:%x\n",(unsigned int )cmd);
//	printk("\narg.........:%d\n",(unsigned int)arg);
	switch(cmd)
	{

		case GPS_PWR_CNTRL:
		//	printk("GPS ON OFF\n");	
			if((unsigned int)arg==1)	
			{
				
				gpio_set_value( GPS_ON_OFF_PIN,1);

			}
			else
				gpio_set_value( GPS_ON_OFF_PIN,0);
			break;
		case GSM_PWR_CNTRL:
			if((unsigned int)arg==1)
			{	
				printk("MODEM RESET LOW........\n");//added printk by bindu
				gpio_set_value(GSM_M_RESET_PIN,0);//added by chandana //sarath 
				printk("MODEM PWR CTRL ON........\n");//added printk by bindu
				gpio_set_value(GSM_PWR_CTRL,1);   	
			}
			else
				gpio_set_value(GSM_PWR_CTRL,0);   	
			break;
		case OPT_CAPPWR_CNTRL:
			//	printk("OPT_CAPPWR_EN:\n");
			if((unsigned int)arg==1)	
				gpio_set_value(OPT_CAPPWR_EN_PIN,1);
			else
				gpio_set_value(OPT_CAPPWR_EN_PIN,0);
			break;
		case HOST_PWR_CNTRL:
			//	printk("HOSTPWR_EN:\n");
			if((unsigned int)arg==1)	
				gpio_set_value(HOST_PWR_CTRL,1);
			else
				gpio_set_value(HOST_PWR_CTRL,0);
			break;
		case LCD_BKL_CNTRL:

			//	printk("LCD_BKL_C:\n");	
			if((unsigned int)arg==1)	
			{
				gpio_set_value(LCD_BKL,1);
				bkl_on=1;

				gpio_set_value(KPD_BKL,1);
			}
			else
			{
				gpio_set_value(LCD_BKL,0);
				bkl_off=1;

				gpio_set_value(KPD_BKL,0);
			}
			break;
		case FLASH_CNTRL:
			if((unsigned int)arg==1 && cam_flag)
			{
				gpio_set_value(CAMERA_FLASH_CTRL,0);
				flash_onflag=1;
				flash_timeout=jiffies+10*HZ;
			}
			else
			{
				gpio_set_value(CAMERA_FLASH_CTRL,1);
				flash_onflag=0;
			}

			break;
		case AUD_PWR_CNTRL:
			//	printk("AUD_PWR_C:\n");    
			if((unsigned int)arg==1)
				gpio_set_value(AUD_PWR,1);
			else
				gpio_set_value(AUD_PWR,0);
			break;
		case BUZZER_CNTRL:
			//	printk("BUZZER:\n");
			if((unsigned int)arg==1)
				gpio_set_value(BUZZ,1);
			else
				gpio_set_value(BUZZ,0);
			break;
		case CAM_PWR_CNTRL:
			//	printk("OTG_CAM:\n");
			if((unsigned int)arg==1  )
			{
				gpio_set_value(CAMERA_PWR_CTRL,1);
				cam_flag=1;
			}		
			else
			{	
				gpio_set_value(CAMERA_PWR_CTRL,0);
				cam_flag=0;	
			}	

			break;
		case IFD_PWR_CNTRL:
			//	printk("IFD_PWR_ENABLE:\n");		
			if((unsigned int)arg==1)
				gpio_set_value (IFD_PWR_ENABLE_PIN,1);
			else
				gpio_set_value (IFD_PWR_ENABLE_PIN,0);
			break;	
		case BLUTH_PWR_CNTRL:
			//	printk("BLUTH_CNTRL:\n");
			if((unsigned int)arg==1)
				gpio_set_value(BT_PWR_CTRL,1);
			else
				gpio_set_value(BT_PWR_CTRL,0);
			break;
		case SELECT_SIM:
			//	printk("SIM SELECT:\n");
			if((unsigned int)arg==1)
				gpio_set_value(SIM_SELECT,1);
			else
				gpio_set_value(SIM_SELECT,0);
			break;
		case SAM_PWR_CNTRL:
			//	printk("SAM_CTRL:\n");
			if((unsigned int)arg==1)
				gpio_set_value(SAM_PWR_CTRL,1);
			else
				gpio_set_value(SAM_PWR_CTRL,0);
			break;
		case GSM_USB_PWR_CNTRL:
			//	printk("GSM_USB_CNTRL:\n");
			if((unsigned int)arg==1)
				gpio_set_value(GSM_USB_PWR_CTRL,1);
			else
				gpio_set_value(GSM_USB_PWR_CTRL,0);
			break;

		case LCD_BKL_TIMEOUT:
			//printk("LCD Backlight timeout\n");
			backlight_timeout = (unsigned int)arg;

			udelay(10);
			break;
		case TOUCH_BUZZ_CNTRL:
			//printk("Touch Buzz control\n");
			if((unsigned int)arg==1)
				touch_buzzer_onoff_flag = 1;
			else
				touch_buzzer_onoff_flag = 0;
			break;
		case KEY_BUZZ_CNTRL:	
			//printk("Key Pad Buzz Control\n");
			if((unsigned int)arg==1)
				key_buzzer_onoff_flag = 1;
			else
				key_buzzer_onoff_flag = 0;
			break;

		case GSM_M_RESET:
				printk("GSM MODEM RESET CNTRL....\n"); //printk added by bindu
			gpio_set_value(GSM_M_RESET_PIN,0);
			printk("After GSM Modem Reset Low\n"); //printk added by bindu	
			gpio_set_value(GSM_M_RESET_PIN,1);
			mdelay(160);
			gpio_set_value(GSM_M_RESET_PIN,0);
			mdelay(500);
			break;

		case BATTER_SENSE:
			drv_battery.batsense_val = gpio_get_value(BAT_SENSE_PIN);
			if (copy_to_user ((struct drv_batsense*)arg,&drv_battery, sizeof(struct drv_batsense)))
				return -EFAULT ;
			break;


	}


	return 0;
}

#if 0
static int get_power()	//Adapater 
{
	char buf[10]="";
	//char buf[10]="0";
	AD7877_Read_batinfo(ADPT_BAT1,buf);
	return simple_strtol(buf, NULL, 0);
}


static int get_battery() //battery read
{
	//	char buf[10]="2001";
	char buf[10]="";
	AD7877_Read_batinfo(BATT_BAT2,buf);
	return simple_strtol(buf, NULL, 0);
}


static unsigned char battery_status(void)
{
	int  filter_val;
	static int pp;
	static int counter=0;
	unsigned int adptr_vol=0;
	unsigned int battr_vol=0;
	unsigned int battery_voltage=0;
	int adaptor_status=0;

	adptr_vol=get_power();
	//	printk("RAJ bat volt 1 val: %d\n:",adptr_vol);

	if(adptr_vol>1000)
	{
		adaptor_status=1;
		//		printk("adapter presence=%d\n",adaptor_status);
	}
	else adaptor_status= 0;

	battr_vol=get_battery();
	//	printk("RAJ Bat volt 2 val: %d\n:",battr_vol);


	filter_val = battr_vol/2;
	battery_voltage = filter_val;

#ifdef DEBUG
	printk("%d %d\n",battery_voltage,adaptor_status);
#endif

	if (battery_voltage > 790)
		return 0;

	else
	{


		/*	printk("Filter Value is %d\n",filter_val);
			printk("Adapter Status  %d\n",adaptor_status);
			printk("Adapter voltage get power  %d\n",get_power());*/

		if ( filter_val < 790 && !adaptor_status )
		{
			if( filter_val < 744 && !adaptor_status )
			{
				if (counter++ > 2 && get_power() < 1000 )
				{
					exit_flag=0;
					printk("Battey Reading-- %d\n",battery_voltage);
					schedule_work(&low_battery_poweroff_wq);
				}

			}
			else  counter=0;

			//printk("Low battery...");

			if ( pp++ < 4 )
			{
				if( buzz_on_flg !=0 )
				{
					gpio_set_value(BUZZ,1); 
					mdelay(60);
					gpio_set_value(BUZZ,0);
				}
			}
			else if (pp==12)
				pp=0;

		}
	}
	return 0;
}


#endif

static int __init ioc_init(void)

{

	int result = 0; 

	result = register_chrdev(MAJORNO, NAME, &ioc_fops);
	if (result < 0) {
		printk("<1> device registration failed \n");
		return result;
	}

	/*	else
		printk("Driver registered successfully\n");

		printk("result=%d\n",result);*/

	printk("1162 IMX6IODRIVER V1.2 Loaded\n");
	imx6sl_hw_init();
	kthread_run(work_thread, NULL, "gl11_kthread");	
	init_timer (&gl11_timer) ;
	gl11_timer.function = gl11_timer_work ;
	gl11_timer.expires = jiffies+10;
	add_timer (&gl11_timer); 


	//	battery_status();
	//	AD7877_Read_batinfo(1,volt);
	//	INIT_WORK(&low_battery_poweroff_wq,poweroff_battery);
	//	INIT_WORK(&rgb_work_struct,rgb_function);

	return result;		/* success */

}


static void gl11_timer_work ( unsigned long arg )
{

	atomic_set (&data_present, 1);
	wake_up_interruptible(&wq);


	//schedule_work(&rgb_work_struct);
	mod_timer(&gl11_timer,(jiffies + 10));
}

static int work_thread(void *arg)
{
	unsigned long jify=0;
	unsigned int  touch_flag=0;
	unsigned int  trc=0;
	unsigned long rtc_jify=0;

	daemonize("gl11_work_kthread");
	rtc_jify = jiffies;

	gpio_set_value(LCD_BKL,1);	
	while ( exit_flag) 
	{


		atomic_set (&data_present, 0);
		if (wait_event_interruptible(wq,(atomic_read (&data_present) )))
		{
			return 0;
		}

		if (touch_release_flag)
			touch_flag++;
		else
		{
			trc=1;
			touch_flag=0;
		}


		if (key_out_flag || ( touch_pnt_out)  || bkl_on )
		{



			jify=jiffies;
			gpio_set_value(LCD_BKL,1);
			//bkpwm_ctl(lcd_bkl_brit);

			if(!touch_buzz)
				touch_pnt_out=0;

#ifdef DEBUG
			printk("%d %d %d %d\n", key_out_flag , touch_pnt_out, buzz_on_flg, buz_counter  );
#endif

			//key_out_flag to be removed from this
			//if ( ( key_out_flag || ( touch_flag && trc) )  && buzz_on_flg && buz_counter )
			if ( (  touch_flag && trc )  && buzz_on_flg && buz_counter )
			{
				if( key_out_flag || ( touch_flag && touch_pnt_out  && buzz_on_flg ))
				{
					gpio_set_value(BUZZ, 1);
					msleep_interruptible(buz_counter*10);
					gpio_set_value(BUZZ, 0);
				}
				if (touch_pnt_out)
				{
					trc=0;
				}
			}

			key_out_flag=0;
			touch_pnt_out=0;
			bkl_on=0;
		}
		else if ( (jiffies -jify) > (backlight_timeout*200) || (bkl_off==1))
		{
			gpio_set_value(LCD_BKL,0);	
			bkl_off=0;
		}




		if (jiffies-rtc_jify>50)
		{
			lcd_bkl_flag++;
			if(lcd_bkl_flag == 60)
			{

				gpio_set_value(LCD_BKL,0);	

			}

			//gpio_set_value(LCD_BKL,1);	
			//	battery_status();

			rtc_jify = jiffies;
			if(flash_onflag && time_after(jiffies,flash_timeout))
			{
				gpio_set_value(CAMERA_FLASH_CTRL,1);
				flash_onflag=0;


			}



		}	


	}
	return 0;
}

static void __exit ioc_cleanup(void)
{
	printk("1162 IMX6IODRIVER V1.2 Unloaded\n");
	imx6sl_hw_deinit();
	del_timer_sync(&gl11_timer);
	exit_flag=0;
	unregister_chrdev(MAJORNO, NAME);

}

module_init(ioc_init);
module_exit(ioc_cleanup);

MODULE_AUTHOR("Chandana priya.s@visiontek.co.in");
MODULE_DESCRIPTION("GL11 IO CONTROL i.MX6 GPIO port");
MODULE_LICENSE("GPL");
