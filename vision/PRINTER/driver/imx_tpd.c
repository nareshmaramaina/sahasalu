/*  device driver for FTP-628MCL103 thermal printer.
 *  printer connected to i.MX25 GPIO port.
 *  Control for Stepping motor and Print head.
 */

#include <linux/types.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/spinlock.h>
#include <linux/major.h>
#include <linux/proc_fs.h>
#include <linux/major.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>           /* for register_chardev, file_operations  etc. */
#include <linux/mm.h>
#include <linux/sched.h>        /* for jiffies */
#include <asm/uaccess.h>        /*  for copy_from_user    */
#include <asm/io.h>             /* to access io memory */

#include <mach/common.h>
#include <mach/hardware.h>
#include <mach/mxc_dvfs.h>
#include <mach/memory.h>
#include <mach/iomux-mx6sl.h>
#include <mach/imx-uart.h>

#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#include "tpd_hardware.h"

//#define DEBUG

//-------------------- Dot-line buffers ---------------------------------------

#define MAX_SCAN_LINE_MEMORY    (100 * 1024) //100 Kilobytes Print Buffer
#define BYTES_PER_SCANLINE      48 //For ATP-48 and other 384 pixel thermal printers
//-------------------- ADC Thresholds -----------------------------------------

#define ADC_NO_ADAPTER  500
#define ADC_MIN_BATTERY 830                     //Battery reading at 6.8V
#define ADC_HOT_HEAD    300                     //NTC Thermistor reading at 75C
//------------------- IOCTL Commands ------------------------------------------

#define ABORT_PRINT             0
#define GET_THERMISTOR_VALUE    1
#define GET_PAPER_STATUS        2
//------------------------- Driver Return Codes -------------------------------

#define MEMORY_ERROR            0x6
#define NO_LINES                0x7
#define WRITE_ERROR             0x8
#define PLATEN_SW_OPEN          0x9
#define NO_PAPER                0xa
#define LOW_BATTERY             0xb
#define MAX_TEMP                0xc
#define STATUS_NO_PAPER -4

//------------------------- Major number --------------------------------
#define MAJORNO 250		/* major no for device */
#define NAME "Thermalprinter"

unsigned int DotCount = 0; /* Dot count of 384 dots */
unsigned int DotCount1=0,DotCount2=0,DotCount3=0,DotCount4=0,DotCount5=0,DotCount6=0;
unsigned int PresentDotCount1=0,PresentDotCount2=0,PresentDotCount3=0,PresentDotCount4=0,PresentDotCount5=0,PresentDotCount6=0;

static int abort2;  

//-------------------------- GPIO Setup ---------------------------------------

void setup_port(void);	/* set port pins in proper mode */
void unsetup_port(void) ;

//-------------------------- Paperfeed Stepper Motor Functions ----------------
static void start_stepmotor(void);
static void stop_stepmotor(void);
static void onestep(void);	//advance paperfeed by one step (4 steps = 1 dot-line)
static int motorstate = 1;	// maintains current step motor state

//------------------ Thermal Printer Interface Functions ----------------------

#if 0
static void PixelPush(int PixVal); //Serial load a pixel into the printer's dot-line buffer
static void LatchTrigger(void); //Latches buffer dot-line into the head driver dot-line 
#endif
//static int PreDotCount = 0 ;	//Dot count of current line

//-------------------------- Print Driver Control Functions -------------------

static int tpd_print(void);
static int tpd_open(struct inode *, struct file *);
static int tpd_release(struct inode *, struct file *);
static ssize_t tpd_read(struct file *, char *, size_t, loff_t *);
static ssize_t tpd_write(struct file *, const char *, size_t, loff_t *);
static long tpd_ioctl(struct file *flip, unsigned int cmd, unsigned long arg);

static int deviceopen = 0;	/* For preventing multiple device opens */
static unsigned char storelines[MAX_SCAN_LINE_MEMORY];	//Memory to store dot image
static unsigned int scanlines;
static int line;			/* at whice scanline we r now */
static char print_case = 0 ;
static char paper_feed = 0;
//static int step_delay = 0 ;
//static unsigned char step_flag = 0 ;
static int Stb_Width=0;


static spinlock_t prn_lock ;
static unsigned long flags;

struct driver_strb{
	int strobewidth_value;
}__attribute__ ((packed));

struct driver_strb driver_strobewidth;
//--------------------- Define the driver interface structure -----------------

static const struct file_operations tpd_fops = {
	.owner = THIS_MODULE,
	.open = tpd_open,
	.read = tpd_read,
	.write = tpd_write,
	.unlocked_ioctl = tpd_ioctl,
	.release = tpd_release,
};

static void start_stepmotor( void )
{
	VHCNTRL_HIGH ;
	IN2_HIGH ;
	IN4_HIGH ;
}


//-----------------------------------------------------------------------------
static void stop_stepmotor(void)
{
	VHCNTRL_LOW ;
	IN1_LOW ;
	IN2_LOW ;
	IN3_LOW ;
	IN4_LOW ;
}
//-----------------------------------------------------------------------------
static long tpd_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	//	printk("IN IOCTL cmd=%d\n",cmd);

	if( cmd == 0 ) {
		abort2 = 0;
		return 0;
	}
	if(cmd == 1){
		if(gpio_get_value(MX6_BRD_PAPERSENSE)&1)
		{
			return -4;
		}
		return 0;
	}
	if(cmd == 3){
		//		ther=read_thermistor();
		//	return ther/4;
		return 0;
	}
	if( cmd == 4 ) { // Normal Font
		if(copy_from_user(&driver_strobewidth,(struct driver_strb*)arg,sizeof(struct driver_strb)))
			return -EFAULT;
		Stb_Width = driver_strobewidth.strobewidth_value;
		//	printk("***************IN IOCTL 4 Stb_Width = %d\n",Stb_Width);
		print_case = 4; //1 23 45 6
		return 0;
	}
	if( cmd == 5 ) { // Bold Font
		if(copy_from_user(&driver_strobewidth,(struct driver_strb*)arg,sizeof(struct driver_strb)))
			return -EFAULT;
		Stb_Width = driver_strobewidth.strobewidth_value;
		//	printk("****************IN IOCTL 5 Stb_Width = %d\n",Stb_Width);
		print_case = 3; //12 34 56
		return 0;
	}
	if( cmd == 6 ) { //BMP
		if(copy_from_user(&driver_strobewidth,(struct driver_strb*)arg,sizeof(struct driver_strb)))
			return -EFAULT;
		Stb_Width = driver_strobewidth.strobewidth_value; 
		//	printk("**************IN IOCTL 6 Stb_Width = %d\n",Stb_Width);
		print_case = 5; //1 2 3 4 5 6
		return 0;
	}
	if(cmd==7)
	{
		if(gpio_get_value(MX6_BRD_PRN_SW)&1)
		{
			return -1;
		}
		else
			return 0;
	}
	if(cmd == 10){
		paper_feed = 1;
		//	printk("##########in driver paperfeed ioctl=%d\n",paper_feed);
		return 0;
	}

	return 0;
}

//-----------------------------------------------------------------------------

static int __init tpd_init(void)
{
	int result = 0; 
	result = register_chrdev(MAJORNO, NAME, &tpd_fops);
	if (result < 0) {
#ifdef DEBUG
		printk("<1> device registration failed \n");
#endif
		return result;
	}
	spin_lock_init(&prn_lock);

	setup_port();
	motorstate = 1;
	return result;		/* success */

}

static void __exit tpd_cleanup(void)
{
	unsetup_port() ;
	unregister_chrdev(MAJORNO, NAME);
}

static int tpd_open(struct inode *inode, struct file *filp)
{
	//printk ("In TPD OPEN\n") ;
	if ( deviceopen ) return -EBUSY;	/* allow one opening only */
	else deviceopen++;
	return 0;
}

static int tpd_release(struct inode *inode, struct file *filp)
{
	//printk ("In TPD RELEASE\n") ;
	deviceopen--;
	return 0;
}

	static ssize_t
tpd_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
	return -EINVAL;		/*  print only,  cant scan */
}

	static ssize_t
tpd_write(struct file *filp, const char *buff, size_t length, loff_t * off)
{	
	unsigned int len = (unsigned int)length;

	int result;
	//	printk("len====%d\n",len);
	if( len > MAX_SCAN_LINE_MEMORY ) {
#ifdef DEBUG
		printk("driver: memory error: ");
#endif
		return MEMORY_ERROR;
	}

	if( len < 1 ) {
#ifdef DEBUG
		printk("driver: memory error: no lines to print");
#endif
		return NO_LINES;
	}

	memset(storelines,0x00,1024*100);

	result = copy_from_user( storelines, buff, length );
	if ( result ) {
#ifdef DEBUG
		printk("Error copying data from application \n");
#endif
		return WRITE_ERROR;
	}
	//	if(paper_feed == 0)
	scanlines = len/BYTES_PER_SCANLINE + 1;
	//	else
	//		scanlines = len;
	//	printk("############### in driver scanlines=%d\n",scanlines);
#ifdef DEBUG
	printk(" %d %i scanlines\n",len,scanlines);
#endif
	line = 0;
	abort2 = 1 ;

	result = tpd_print();
	return result;
}


static void onestep(void)
{
	switch (motorstate) {
		case 1:
			IN1_HIGH ;
			IN2_LOW ;
			IN3_LOW ;
			IN4_HIGH ;
			motorstate = 2;
			break;

		case 2:
			IN1_LOW ;
			IN2_LOW ;
			IN3_LOW ;
			IN4_HIGH ;
			motorstate = 3;
			break;

		case 3:
			IN1_LOW ;
			IN2_HIGH ;
			IN3_LOW ;
			IN4_HIGH ;
			motorstate = 4;
			break;

		case 4:
			IN1_LOW ;
			IN2_HIGH ;
			IN3_LOW ;
			IN4_LOW ;
			motorstate = 5;
			break;

		case 5:
			IN1_LOW ;
			IN2_HIGH ;
			IN3_HIGH ;
			IN4_LOW ;
			motorstate = 6;
			break;

		case 6:
			IN1_LOW ;
			IN2_LOW ;
			IN3_HIGH ;
			IN4_LOW ;
			motorstate = 7;
			break;

		case 7:
			IN1_HIGH ;
			IN2_LOW ;
			IN3_HIGH ;
			IN4_LOW ;
			motorstate = 8;
			break;

		case 8:
			IN1_HIGH ;
			IN2_LOW ;
			IN3_LOW ;
			IN4_LOW ;
			motorstate = 1;
			break;

	}
}



static int tpd_print(void)
{
	static unsigned char mask ;
	static int pixel = 0, bits; /*,Stb_Width=0,nop=0*/;
	//static long Stb_Width=0;

	//	printk("######################IN DRIVER Stb_Width = %d\n",Stb_Width);
	//	printk("######################PAPER_FEED= %d\n",paper_feed);
	//	if(paper_feed==0 && (Stb_Width >1500 || Stb_Width <=0))
	//		return -1;
	spin_lock_irqsave(&prn_lock, flags);

	STROBE1_LOW ; STROBE2_LOW ;STROBE3_LOW ;STROBE4_LOW ;STROBE5_LOW ;STROBE6_LOW ;

	start_stepmotor();
	//	printk("##############in tpd_print scanlines ======%d,paperfeed ====%d\n",scanlines,paper_feed);
	while((line < scanlines)&&abort2){
		if(line == 0){
			for ( pixel = 0; pixel < 48; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						if (pixel < 8) DotCount6++;
						else if (pixel < 16 )DotCount5++;
						else if (pixel < 24 )DotCount4++;
						else if (pixel < 32 )DotCount3++;
						else if (pixel < 40 )DotCount2++;
						else DotCount1 ++;
					}
					mask = mask >> 1;
				}
			}
			line ++ ;
		}// end of if
		udelay(8) ;
		LATCH_LOW ;
		udelay(7) ;
		LATCH_HIGH ;
		udelay(10) ;
		DotCount = DotCount1 + DotCount2 + DotCount3 + DotCount4 + DotCount5 + DotCount6;
		if(DotCount == 0){
			STROBE6_LOW ; STROBE5_LOW ;STROBE4_LOW ;STROBE3_LOW ;STROBE2_LOW ;STROBE1_LOW ;
			for ( pixel = 0; pixel < 24; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						if (pixel < 8) PresentDotCount6++;
						else if (pixel < 16 )PresentDotCount5++;
						else if (pixel < 24 )PresentDotCount4++;
					}
					mask = mask >> 1;
				}
			}
			udelay(500-192) ;
			onestep() ;
			for ( ; pixel < 48; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						if (pixel < 32 )PresentDotCount3++;
						else if (pixel < 40 )PresentDotCount2++;
						else PresentDotCount1 ++;
					}
					mask = mask >> 1;
				}
			}
			udelay(500-192) ;
			onestep() ;
		}
		else if (DotCount > 0 && DotCount < 128)
		{
			STROBE6_HIGH ;
			STROBE5_HIGH ;
			STROBE4_HIGH ;  
			for ( pixel = 0; pixel < 24; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						if (pixel < 8) PresentDotCount6++;
						else if (pixel < 16 )PresentDotCount5++;
						else if (pixel < 24 )PresentDotCount4++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount6+DotCount5+DotCount4-192) ;
			STROBE6_LOW ;
			STROBE5_LOW ;
			STROBE4_LOW ;

			onestep();

			STROBE3_HIGH ;
			STROBE2_HIGH ;
			STROBE1_HIGH ;
			for ( ; pixel < 48; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						if (pixel < 32 )PresentDotCount3++;
						else if (pixel < 40 )PresentDotCount2++;
						else PresentDotCount1 ++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount3+DotCount2+DotCount1-192) ;
			STROBE3_LOW ;
			STROBE2_LOW ;
			STROBE1_LOW ;
			onestep();
		}
		else if (DotCount > 127 && DotCount < 256){
			STROBE6_HIGH ;
			STROBE5_HIGH ;
			for ( pixel = 0; pixel < 16; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						if (pixel < 8) PresentDotCount6++;
						else if (pixel < 16 )PresentDotCount5++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount6+DotCount5-128) ;
			STROBE6_LOW ;
			STROBE5_LOW ;
			onestep();
			STROBE4_HIGH ;
			STROBE3_HIGH ;
			for ( ; pixel < 32; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						if (pixel < 24 )PresentDotCount4++;
						else if (pixel < 32 )PresentDotCount3++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount4+DotCount3-128) ;
			STROBE4_LOW ;
			STROBE3_LOW ;

			STROBE2_HIGH ;
			STROBE1_HIGH ;
			for ( ; pixel < 48; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						if (pixel < 40 )PresentDotCount2++;
						else PresentDotCount1 ++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount2+DotCount1-128) ;
			STROBE2_LOW ;
			STROBE1_LOW ;
			onestep();
		}
		else if(DotCount > 255){
			STROBE6_HIGH ;
			for ( pixel = 0; pixel < 8; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						PresentDotCount6++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount6-64) ;
			STROBE6_LOW ;

			STROBE5_HIGH ;
			for ( ; pixel < 16; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						PresentDotCount5++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount5-64) ;
			STROBE5_LOW ;

			STROBE4_HIGH ;
			for ( ; pixel < 24; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						PresentDotCount4++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount4-64) ;
			STROBE4_LOW ;
			onestep() ;
			STROBE3_HIGH ;
			for ( ; pixel < 32; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						PresentDotCount3++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount3-64) ;
			STROBE3_LOW ;

			STROBE2_HIGH ;
			for ( ; pixel < 40; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						PresentDotCount2++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount2-64) ;
			STROBE2_LOW ;

			STROBE1_HIGH ;
			for ( ; pixel < 48; pixel++ ) {
				mask = 0x80;
				for( bits = 1; bits <= 8; bits++ ) {
					if ( (storelines[line * 48 + pixel] & mask ) == 0 ) {
						DATAIN_LOW ;
						CLK_HIGH ;
						CLK_LOW ;
					} else {
						DATAIN_HIGH ;
						CLK_HIGH ;
						CLK_LOW ;
						PresentDotCount1 ++;
					}
					mask = mask >> 1;
				}
			}
			udelay(Stb_Width+DotCount1-64) ;
			STROBE1_LOW ;
			onestep() ;
		}

		DotCount = DotCount1 = DotCount2 = DotCount3 = DotCount4 = DotCount5 = DotCount6 = 0;
		DotCount1 = PresentDotCount1 ;
		DotCount2 = PresentDotCount2 ;
		DotCount3 = PresentDotCount3 ;
		DotCount4 = PresentDotCount4 ;
		DotCount5 = PresentDotCount5 ;
		DotCount6 = PresentDotCount6 ;
		PresentDotCount1 = PresentDotCount2 = PresentDotCount3 = PresentDotCount4 = PresentDotCount5 = PresentDotCount6 = 0;
		line ++ ;

	}

	paper_feed=0;
	Stb_Width = 0;	
	stop_stepmotor();
	DotCount = DotCount1 = DotCount2 = DotCount3 = DotCount4 = DotCount5 = DotCount6 = 0;
	spin_unlock_irqrestore(&prn_lock, flags);
	return 0;
}//end of function tpd_print

module_init(tpd_init);
module_exit(tpd_cleanup);

MODULE_AUTHOR("malleswari@visiontek.co.in");
MODULE_DESCRIPTION("FTP-628MCL103 ThermalPrinterDriver, connected to i.MX25 GPIO port");
MODULE_LICENSE("GPL");
