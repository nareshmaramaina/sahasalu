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

#include"../arch/arm/plat-mxc/include/mach/iomux-mx6sl.h"
#include "ioc_hardware.h"

#define MAJORNO 235		/* major no for device */
#define NAME "ioc"

#define ADPT_BAT1                       0X01
#define BATT_BAT2              		0x02
#define PRN_TMP				0x03		

struct drv_batsense
{
	int batsense_val;
}drv_battery;


//extern volatile int backlight_timeout ;
//extern volatile int key_buzzer_onoff_flag ;
//extern volatile int touch_buzzer_onoff_flag ;

DECLARE_WAIT_QUEUE_HEAD(wq);


/*  External Varibles and functions  */

extern int touch_pnt_out;    // notification for touch pont out
extern char key_out_flag;    // notification for key out flag

extern char touch_release_flag;  // Dummy 


// Local varibles  and functions


static int work_thread(void *arg);

static atomic_t data_present=ATOMIC_INIT(0);

static int bklight_timeout = 16;   //Backlight time out 

static int lcd_rgb_flag = 0; // Back_light on and off flag  

static int cam_flag  = 0;          // Verification for Camera ON or Not 
static int flash_onflag = 0;       // Camera flash on off flag
unsigned long int flash_timeout=0; // Camera timeout flag

static int exit_flag=1; // kernel thread exit flag

static int buz_counter=2; // Varible for buz on time for kp and ts min of 1 and max of 5

static int bkl_on_timer=0;// Back light on flag and glows for bklight_timeout  
static int bkl_cont_on=0; // Varible for continus on for Bk lite

static int buzz_on_flg=0; // Buzzer continuous on
static int touch_buzz=1;  // you want to enable buzzer on touch -- default on
static int key_buzz=1;     // you want to enable buzzer on key press   -- default on

static int lcd_brit = 0x40;  // varible with default briteness
static int lcd_cont = 0x08;  // varible with default contrast



static void gl11_timer_work  (unsigned long arg) ;
static struct timer_list gl11_timer ;
static int ioc_open(struct inode *, struct file *);
static int ioc_release(struct inode *, struct file *);

//static int get_thermister(void);

static int ioc_open(struct inode *, struct file *);
static int ioc_release(struct inode *, struct file *);
static ssize_t ioc_read(struct file *, char *, size_t, loff_t *);
static ssize_t ioc_write(struct file *, const char *, size_t, loff_t *);
static int ioc_ioctl(struct file *flip, unsigned int cmd, unsigned long arg);

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

static int ioc_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	int ret_val=0;
	switch(cmd)
	{

		case GPS_PWR_CNTRL:
			//	printk("GPS ON OFF\n");	
			if((unsigned int)arg==1)	
				gpio_set_value( GPS_ON_OFF_PIN,1);
			else
				gpio_set_value( GPS_ON_OFF_PIN,0);
			break;
		case GSM_PWR_CNTRL:
			//	printk("GSM POWER CONTROL\n");
			if((unsigned int)arg==1)	
				gpio_set_value(GSM_PWR_CTRL,1);   	
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
			// Lcd ON with timer
			if((unsigned int)arg==1)	
				bkl_on_timer=1;
			else 
				bkl_on_timer=0;
			break;
		case LCD_BKL_CONT:
			//  LCD BKL on continuous	
			if((unsigned int)arg==1)
			{
				bkl_cont_on=1;
				mdelay(10);
				bkl_cont_on=1;
			}
			else
				bkl_cont_on=0;
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
			{
				gpio_set_value(BUZZ,1);
				buzz_on_flg=1;
				gpio_set_value(BUZZ,1);
			}
			else
			{
				gpio_set_value(BUZZ,0);
				buzz_on_flg=0;
				gpio_set_value(BUZZ,0);
			}

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
			bklight_timeout  = (unsigned int)arg;
			udelay(10);
			break;	

			/*
			   case LCD_BKL_TIMEOUT:
			//printk("LCD Backlight timeout\n");
			bklight_timeout  = (unsigned int)arg;
			if ( bklight_timeout < 16)
			bklight_timeout=16;
			else if (bklight_timeout > 90)
			bklight_timeout = 90;
			udelay(10);
			break; */

		case TOUCH_BUZZ_CNTRL:
			//printk("Touch Buzz control\n");
			if((unsigned int)arg==1)
				touch_buzz = 1;
			else
				touch_buzz = 0;
			break;
		case KEY_BUZZ_CNTRL:	
			//printk("Key Pad Buzz Control\n");
			if((unsigned int)arg==1)
				key_buzz = 1;
			else
				key_buzz =  0;
			break;

		case GSM_M_RESET:
			//	printk("GSM MODEM RESET CNTRL:\n");
			gpio_set_value(GSM_M_RESET_PIN,0);
			mdelay(10);
			gpio_set_value(GSM_M_RESET_PIN,1);
			mdelay(250);
			gpio_set_value(GSM_M_RESET_PIN,0);
			//mdelay(1000); delay to be added in app
			break;
		case BRIGHTNESS:
			if((unsigned int)arg)
				lcd_brit=(unsigned int)arg;
			else
				lcd_brit=0x40;	
			lcd_rgb_flag=1;
			mdelay(10);

			break;
		case CONTRAST:
			if((unsigned int )arg)
				lcd_cont=(unsigned int)arg;
			else
				lcd_cont=0x08;
			lcd_rgb_flag=1;
			mdelay(10);
			break;

		case BATTER_SENSE:

			drv_battery.batsense_val = gpio_get_value(BAT_SENSE_PIN);
			if (copy_to_user ((struct drv_batsense*)arg,&drv_battery, sizeof(struct drv_batsense)))

				return -EFAULT ; /*
						    Batt.AdapPresent= adaptor_status;
						    Batt.BattSt     =  gpio_get_value(BAT_SENSE_PIN);
						    Batt.BattVt     = battery_voltage;

#ifdef DEBUG
printk("adaptor_status:%d\t charging_status:%d\t battery_voltage:%d\n",adaptor_status,charging_status,battery_voltage);
#endif

if (copy_to_user ((struct BatteryStatus*)arg,&Batt, sizeof(struct BatteryStatus)))
return -EFAULT ;
break;

break;
case PRN_THERMISTER:
ret_val=get_thermister();
printk("Themister stat=%d\n",ret_val);
Therm.thermister_status=ret_val;

if (copy_to_user ((struct Thermister*)arg,&Therm, sizeof(struct Thermister)))
return -EFAULT ; */
			break;
		case BUZZ_TS_KP_TIME:
			if((unsigned int)arg)
				buz_counter=arg;
			else 
				buz_counter=2;
			break;
	}


	return 0;
}

/*
   static int get_power(void)	//Adapater 
   {
   char buf[10]="";
   AD7877_Read_batinfo(ADPT_BAT1,buf);
   return simple_strtol(buf, NULL, 0);
   }


   static int get_battery(void) //battery read
   {
   char buf[10]="";
   AD7877_Read_batinfo(BATT_BAT2,buf);
   return simple_strtol(buf, NULL, 0);
   }


   static int get_thermister(void) //battery read
   {
   char buf[10]="";
   AD7877_Read_batinfo(PRN_TMP,buf);
   return simple_strtol(buf, NULL, 0);
   }



   static unsigned char battery_status(void)
   {
   static int pp;
   static int counter=0;
   unsigned int adptr_vol=0;
   unsigned int battr_vol=0;

   adptr_vol=get_power();

   if(adptr_vol > 1000)
   {
   adaptor_status=1;
   }
   else adaptor_status= 0;

   battr_vol = get_battery();

   battery_voltage = battr_vol/2;

//printk("%d %d\n",battery_voltage,adaptor_status);

if (battery_voltage > 790)
return 0;

else
{
if (  battery_voltage < 790 && !adaptor_status )
{
if( battery_voltage < 744 && !adaptor_status )
{
if (counter++ > 2 && get_power() < 1000 )
{
exit_flag=0;
printk("Battey Reading-- %d\n",battery_voltage);
schedule_work(&low_battery_poweroff_wq);
}

}
else  counter=0;

if ( pp++ < 4 )
{
gpio_set_value(BUZZ,1); 
mdelay(60);
gpio_set_value(BUZZ,0);
}
else if (pp==12)
	pp=0;

	}
}
return 0;
}

	*/
static void gl11_timer_work ( unsigned long arg )
{

	atomic_set (&data_present, 1);
	wake_up_interruptible(&wq);
	mod_timer(&gl11_timer,(jiffies + 10));
}

static int work_thread(void *arg)
{
	unsigned long jify=0;
	unsigned long rtc_jify=0;
	unsigned long rgb_jify=0;	

	int bkl_on_flag=0;	

	daemonize("gl11_work_kthread");

	rtc_jify = jiffies+50;

	rgb_jify = rtc_jify + 100;  

	while ( exit_flag) 
	{

		atomic_set (&data_present, 0);

		if (wait_event_interruptible(wq,(atomic_read (&data_present) )))
		{
			return 0;
		} 

		if ( key_out_flag || touch_pnt_out || bkl_on_timer || bkl_cont_on )
		{
			gpio_set_value(LCD_BKL,1); // bkl _on

			bkl_on_flag = 1;

			if( !touch_buzz ) // When touch buzzer disabled 
				touch_pnt_out = 0;

			if (  !key_buzz)  // when key pad buzze disabled 
				key_out_flag = 0;

			if ( key_out_flag || touch_pnt_out || buzz_on_flg )
			{
				gpio_set_value(BUZZ, 1);

				if (!buzz_on_flg)
				{
					msleep_interruptible(buz_counter*10);
					gpio_set_value(BUZZ, 0);
				}
			}

			if (key_out_flag)
				key_out_flag=0;
			if (touch_pnt_out)
				touch_pnt_out=0;
			if (bkl_on_timer)
				bkl_on_timer=0;

			jify = jiffies + bklight_timeout * 100;
		}

		else if ( ( (time_after_eq( jiffies, jify )  && bkl_on_flag ) &&  !bkl_cont_on ))
		{
			gpio_set_value(LCD_BKL,0);	
			bkl_on_flag=0;
		}


		if (unlikely(flash_onflag && time_after_eq(jiffies,flash_timeout)))
		{
			gpio_set_value(CAMERA_FLASH_CTRL,1);
			flash_onflag=0;
		}



	}
	return 0;
}

static int __init ioc_init(void)

{

	int result = 0;

	result = register_chrdev(MAJORNO, NAME, &ioc_fops);
	if (result < 0) {
		printk("<1> device registration failed \n");
		return result;
	}

	imx6sl_hw_init();
	kthread_run(work_thread, NULL, "gl11_kthread");
	init_timer (&gl11_timer) ;
	gl11_timer.function = gl11_timer_work ;
	gl11_timer.expires = jiffies+10;
	add_timer (&gl11_timer);

	return result;          /* success */

}


static void __exit ioc_cleanup(void)
{
	gpio_set_value(BUZZ,0); // buzzer off	
	exit_flag=0;
	msleep(100);
	del_timer_sync(&gl11_timer);
	imx6sl_hw_deinit();
	unregister_chrdev(MAJORNO, NAME);
}

module_init(ioc_init);
module_exit(ioc_cleanup);

MODULE_AUTHOR("Chandana priya.s@visiontek.co.in");
MODULE_DESCRIPTION("GL11 IO CONTROL i.MX6 GPIO port");
MODULE_LICENSE("GPL");
