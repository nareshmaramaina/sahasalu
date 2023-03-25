/* Magnetic swipe card reader device driver
 * Implemented for BS300H magswipe reader IC 
 * Interfaced with i.MX258 freescale Processor
 * 1. Port 4 11 --- Card Load Signal
 * 2. Port 4 10 --- Track 1 Clock
 * 3. Port 4 6 --- Track 2 Clock
 * 4. Port 4 12 --- Track 1 Data
 * 5. Port 4 5 --- Track 2 Data
 * 6. Port 4 9 --- Track 3 Clock 
 * 7. Port 4 7 --- Track 3 Data  
 * 8.  --- Power down mode control 
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
#include <asm/mach/irq.h>


/*--------------------------------Major No of device------------------------------------*/
#define MAJORNO 240            
/*--------------------------------------------------------------------------------------*/
/*#define MS_PAD_CTL (PAD_CTL_PKE_ENABLE | PAD_CTL_PUE_PUD | \
                         PAD_CTL_22K_PU | PAD_CTL_ODE_OpenDrain )*/
#define MS_PAD_CTL (PAD_CTL_PKE_ENABLE)
/*--------------------------------Tracks Data defines----------------------------------------*/
#define SS1     0x8A
#define ES1     0x3F
#define SS2     0x58
#define ES2     0x3F
#define TRACK1  0x01
#define TRACK2  0x02
#define TRACK3  0x03
/*--------------------------------------------------------------------------------------*/

#define GPIO_IMR	0x14


/*--------------------------------------------------------------------------------------*/
/* Hardware Layer */
/* OLD Configuration 
#define MS_CARD_LOAD            MX25_PIN_D9 
#define MS_TRACK1_CLK           MX25_PIN_D10 
#define MS_TRACK1_DATA          MX25_PIN_D8 
#define MS_TRACK2_CLK           MX25_PIN_D14 
#define MS_TRACK2_DATA          MX25_PIN_D15 
#define MS_TRACK3_CLK           MX25_PIN_D11 
#define MS_TRACK3_DATA          MX25_PIN_D13 */

#define MS_CARD_LOAD            IMX_GPIO_NR(5, 12) 
#define MS_TRACK1_CLK           IMX_GPIO_NR(5, 14) 
#define MS_TRACK1_DATA          IMX_GPIO_NR(5, 15) 
#define MS_TRACK2_CLK           IMX_GPIO_NR(5, 8) 
#define MS_TRACK2_DATA          IMX_GPIO_NR(5, 11) 
#define MS_TRACK3_CLK           IMX_GPIO_NR(5, 6) 
#define MS_TRACK3_DATA          IMX_GPIO_NR(5, 13) 
//#define MS_PWRDN          	MX25_PIN_D14 

#define ms_set_gpio_value(gpio_pin,val) gpio_set_value(gpio_pin,val)
#define ms_get_gpio_value(gpio_pin)     gpio_get_value(gpio_pin)

/*--------------------------------------------------------------------------------------*/

/*--------------------------------Global Variables--------------------------------------*/
//static struct timer_list kt_timer;      // kernel timer structure
static spinlock_t mag_spin_lock;
static int deviceopen = 0;      /* For preventing multiple device opens */
static int ready, firstint, pc26, pc28 ,pc30 ;
static int valid1, valid2, valid3 ;
//static int mscr_wait_flag = 0;
//static int trackone[1024 * 1], tracktwo[1024 * 1],trackthree[1024 * 1];
static int trackone[2048], tracktwo[2048],trackthree[2048];
static char data1[256], data2[256],data3[256];
int /*wait1 = 0,*/ count1 = 0, count2 = 0 ,count3 = 0 ;
int card_load, clk1, clk2, clk3 ;
/*--------------------------------------------------------------------------------------*/

/*--------------------------------Functions---------------------------------------------*/
static void setup_port(void) ; /* Setup port pins to work as a GPIOs and interrupts*/
static void cleanup_port(void); /* Disable interrupts */
static void makeready(void); /* Initialize required variables */
//static void mscr_wait(unsigned long arg); /* kernel timer handler */
static void kt_timedout(unsigned long arg); /* time out function */
static int GetTrackDataRev(int *data, char *dest, int cnt, int track); /* Process reverse direction data */
static int GetTrackDataFw(int *data, char *dest, int cnt, int track); /* Process forward direction data */
static int chk_parity(unsigned char x) ; 
/*--------------------------------------------------------------------------------------*/

/*----------------------------Card Load Signal Interrupt--------------------------------*/
static irqreturn_t card_load_interrupt(int irq, void *dev_id)
{
        kt_timedout(0);
        return IRQ_HANDLED;
}
/*--------------------------------------------------------------------------------------*/

/*----------------------------Track 1 clock Interrupt-----------------------------------*/

static irqreturn_t clk1_interrupt(int irq, void *dev_id)
{
        if ( !ready ) 
		return -1;
        if( pc26 < 1024 ) {
        	//if((__raw_readl(0xfc2d0008) >> 6)&1)
        	if((__raw_readl(0xf40ac008) >> 15)&1)
                	trackone[pc26]=0x0;
           	else
               		trackone[pc26]=0x1;
                pc26++;
      	}
        return IRQ_HANDLED;
}
/*--------------------------------------------------------------------------------------*/

/*----------------------------Track 2 clock Interrupt-----------------------------------*/

static irqreturn_t clk2_interrupt(int irq, void *dev_id)
{
        if ( !ready ) 
		return -1;
     	if( pc28 < 1024 ){
       		//if((__raw_readl(0xfc2d0008) >> 8)&1)
       		if((__raw_readl(0xf40ac008) >> 11)&1)
                	tracktwo[pc28]=0x0;
               	else
                       	tracktwo[pc28]=0x1;
               	pc28++;
      	}
        return IRQ_HANDLED;
}

/*--------------------------------------------------------------------------------------*/

/*----------------------------Track 3 clock Interrupt-----------------------------------*/

static irqreturn_t clk3_interrupt(int irq, void *dev_id)
{
        if ( !ready ) 
		return -1;
     	if( pc30 < 1024 ){
        	//if((__raw_readl(0xfc29c008) >> 7)&1)
        	if((__raw_readl(0xf40ac008) >> 13)&1)
                	trackthree[pc30]=0x0;
              	else
                   	trackthree[pc30]=0x1;
                pc30++;
      	}
        return IRQ_HANDLED;
}
/*--------------------------------------------------------------------------------------*/

/*---------------------------OPEN file operation----------------------------------------*/
static int mscrd_open(struct inode *inode, struct file *filp)
{
	if ( deviceopen ) return -EBUSY;        /* allow one opening only */
        else deviceopen ++;
        spin_lock_init(&mag_spin_lock);
        return 0;
}
/*--------------------------------------------------------------------------------------*/

/*---------------------------CLOSE file operation----------------------------------------*/
static int mscrd_close(struct inode *inode, struct file *filp)
{
        cleanup_port();
        deviceopen --;
        return 0;
}
/*--------------------------------------------------------------------------------------*/

/*---------------------------READ file operation----------------------------------------*/
static ssize_t mscrd_read(struct file *flip, char *buf, size_t length, loff_t *off)
{
        if( length == 0) {
		valid1 = 0 ;
		valid2 = 0 ;
		valid3 = 0 ;
                 spin_lock_irq(&mag_spin_lock);
                 cleanup_port();
                 spin_unlock_irq(&mag_spin_lock);
                return 0;
        }
        spin_lock_irq(&mag_spin_lock);
//irqs to be enabled
//	__raw_writel(( __raw_readl(0xfc29c000 + GPIO_IMR) | 0xe40  ),(0xfc29c000 + GPIO_IMR)) ;
	__raw_writel(( __raw_readl(0xf40ac000 + GPIO_IMR) | 0x5140  ),(0xf40ac000 + GPIO_IMR)) ;
//	__raw_writel(( __raw_readl(0xf40a4000 + GPIO_IMR) | 0x5  ),(0xf40a4000 + GPIO_IMR)) ;
        spin_unlock_irq(&mag_spin_lock);
	/* */
        if( length == 3) {
                char state[3] = { 0, 0, 0 };
                if( valid1 == 1||valid2==1||valid3==1) {
                        state[0] = 1;
                        if(copy_to_user(buf,state,2)){
                                printk ("copy_to_user1 error\n") ;
                                return -EFAULT ;
                        }
                        return 2;
                } else {
                        if(copy_to_user(buf,state,2)){
                                printk ("copy_to_user2 error\n") ;
                                 return -EFAULT ;
                        }
                        return 2;
                }
        }
	/* */
        if( length == 501 ) {
                if( valid1 == 1) {
                        if(copy_to_user(buf,data1,250)){
                                printk ("copy_to_user3 error\n") ;
                 		spin_lock_irq(&mag_spin_lock);
                 		cleanup_port();
                 		spin_unlock_irq(&mag_spin_lock);
                                 return -EFAULT ;
                        }
                 	spin_lock_irq(&mag_spin_lock);
                 	cleanup_port();
                 	spin_unlock_irq(&mag_spin_lock);
		//	cleanup_port () ;
                        return 0;
                }
        }
        if( length == 502 ) {
                if( valid2 == 1) {
                        if(copy_to_user(buf,data2,250)){
                                printk ("copy_to_user4 error\n") ;
                 		spin_lock_irq(&mag_spin_lock);
                 		cleanup_port();
                 		spin_unlock_irq(&mag_spin_lock);
			//	cleanup_port () ;
                                 return -EFAULT ;
                        }
                 	spin_lock_irq(&mag_spin_lock);
                 	cleanup_port();
                 	spin_unlock_irq(&mag_spin_lock);
		//	cleanup_port () ;
                        return 0;
                }
        }
	/* Track 3 to be Tested */
        if( length == 503 ) {
                if( valid3 == 1) {
                        if(copy_to_user(buf,data3,250)){
                                printk ("copy_to_user5 error\n") ;
                 		spin_lock_irq(&mag_spin_lock);
                 		cleanup_port();
                 		spin_unlock_irq(&mag_spin_lock);
				//cleanup_port () ;
                                 return -EFAULT ;
                        }
                 	spin_lock_irq(&mag_spin_lock);
                 	cleanup_port();
                 	spin_unlock_irq(&mag_spin_lock);
			//cleanup_port () ;
                        return 0;
                }
        }
        spin_lock_irq(&mag_spin_lock);
       	cleanup_port();
       	spin_unlock_irq(&mag_spin_lock);
        //printk ("Final Error\n") ;
        return -1;
}
/*--------------------------------------------------------------------------------------*/

/*--------------------------------Setup GPIO Port pins----------------------------------*/
static void setup_port(void)
{
        mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_DAT4__GPIO_5_12) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_CMD__GPIO_5_14) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_CLK__GPIO_5_15) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_DAT1__GPIO_5_8) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_DAT0__GPIO_5_11) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_DAT3__GPIO_5_6) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_DAT2__GPIO_5_13) ;

        gpio_request(MS_CARD_LOAD,"cardload") ;
        gpio_request(MS_TRACK1_CLK,"tk1clk") ;
        gpio_request(MS_TRACK1_DATA,"tk1data") ;
        gpio_request(MS_TRACK2_CLK,"tk2clk") ;
        gpio_request(MS_TRACK2_DATA,"tk2data") ;
        gpio_request(MS_TRACK3_CLK,"tk3clk") ;
        gpio_request(MS_TRACK3_DATA,"tk3data") ;

        gpio_direction_input(MS_CARD_LOAD);
        gpio_direction_input(MS_TRACK1_CLK);
        gpio_direction_input(MS_TRACK1_DATA);
        gpio_direction_input(MS_TRACK2_CLK);
        gpio_direction_input(MS_TRACK2_DATA);
        gpio_direction_input(MS_TRACK3_CLK);
        gpio_direction_input(MS_TRACK3_DATA);


// IRQ 
	card_load = gpio_to_irq(MS_CARD_LOAD) ;
	clk1 = gpio_to_irq(MS_TRACK1_CLK) ;
	clk2 = gpio_to_irq(MS_TRACK2_CLK) ;
	clk3 = gpio_to_irq(MS_TRACK3_CLK) ;
#if 0
	card_load = IOMUX_TO_IRQ(MS_CARD_LOAD) ;
	clk1 = IOMUX_TO_IRQ(MS_TRACK1_CLK) ;
	clk2 = IOMUX_TO_IRQ(MS_TRACK2_CLK) ;
	clk3 = IOMUX_TO_IRQ(MS_TRACK3_CLK) ;
#endif
// Set IRQ Type
	irq_set_irq_type(card_load, IRQ_TYPE_EDGE_RISING) ;
	irq_set_irq_type(clk1, IRQ_TYPE_EDGE_FALLING) ;
	irq_set_irq_type(clk2, IRQ_TYPE_EDGE_FALLING) ;
	irq_set_irq_type(clk3, IRQ_TYPE_EDGE_FALLING) ;
}
/*--------------------------------------------------------------------------------------*/

/*-------------------------------- Disable Interrupts----------------------------------*/
static void cleanup_port(void)
{
// irqs to be disabled

//	__raw_writel(( __raw_readl(0xfc29c000 + GPIO_IMR) &~ 0xe40  ),(0xfc29c000 + GPIO_IMR)) ;
	//__raw_writel(( __raw_readl(0xfc2d0000 + GPIO_IMR) &~ 0x2b0  ),(0xfc2d0000 + GPIO_IMR)) ;
	__raw_writel(( __raw_readl(0xf40ac000 + GPIO_IMR) &~ 0x5140  ),(0xf40a0000 + GPIO_IMR)) ;
//	__raw_writel(( __raw_readl(0xf40a4000 + GPIO_IMR) &~ 0x5  ),(0xf40a4000 + GPIO_IMR)) ;
}
/*--------------------------------------------------------------------------------------*/

/*-----------------------------Initialize required variables----------------------------*/
static void makeready()
{
        pc26 = 0;
        pc28 = 0;
	pc30 = 0 ; 
        firstint = 1;
        ready = 1;
}
/*--------------------------------------------------------------------------------------*/

/*---------------------------Timeout Function--------------------------------------------*/
static void kt_timedout(unsigned long arg)
{
        int  val1r = -1, val1f = -1, val2r = -1, val2f = -1,val3r = -1, val3f = -1;
                                                                                                                             
        ready = 0;             
	//printk ("%d %d %d\n",pc26,pc28,pc30) ;
#if 0
        if(/*pc26 < 10 || */pc28 < 10/*|| pc30 < 10*/){
                goto INVALID;
        }
#endif
        strcpy(data3,"NULL");
	valid3 = 0 ;
        val3f = GetTrackDataFw(&trackthree[1], data3, pc30 - 1, TRACK3);
        if(val3f < 0)
        {
                val3r = GetTrackDataRev(&trackthree[1], data3, pc30 - 1, TRACK3);
                if( val3r < 0 )
			valid3 = 0 ;
		else
			valid3 = 1 ; //goto INVALID;
        }
	else
		valid3 = 1 ;
        strcpy(data1,"NULL");
	valid1 = 0 ;
        val1f = GetTrackDataFw(&trackone[1], data1, pc26 - 1, TRACK1);
        if(val1f < 0)
        {
//		printk ("Track1 Error\n") ;
                val1r = GetTrackDataRev(&trackone[1], data1, pc26 - 1, TRACK1);
                if( val1r < 0 ) 
			valid1 = 0 ;
		else
			valid1 = 1 ; //goto INVALID;
        }
	else
		valid1 = 1 ;
        strcpy(data2,"NULL");
	valid2 = 0 ;
        val2f = GetTrackDataFw(&tracktwo[1], data2, pc28 - 1, TRACK2);
        if(val2f < 0)
        {
//		printk ("Track2 Error\n") ;
                val2r = GetTrackDataRev(&tracktwo[1], data2, pc28 - 1, TRACK2);
                if( val2r < 0 )
			valid2 = 0 ;
		else
			valid2 = 1 ; //goto INVALID;
        }
	else
		valid2 = 1 ;
        makeready();
        return;
//INVALID:
//        makeready();
//        return;
}
/*--------------------------------------------------------------------------------------*/

/*-----------------------Process Forward direction swipe data---------------------------*/
static int GetTrackDataFw(int *data, char *dest, int cnt, int track)
{
        int itr, bits, jj;
        unsigned char ch, csum;

        ch = 0;
        csum=0;jj=0;
        for (itr = 1; itr < cnt; itr++) {
                if (data[itr] > 0x1)
                        continue;
                ch = ch >> 1;
                if (data[itr] == 0x0)
                        ch = ch | 0x0;
                else
                        ch = ch | 0x80;
                                                                                                                             
                if ((ch & 0xfe) == SS1 && track == TRACK1) {
                        ch = ch & 0x7e;
                        ch= ch >>1;
                        csum = csum ^ ch;
                        dest[jj++]=ch+0x20;
                        itr++;
                        break;
                } else if ((ch & 0xf8) == SS2 && track == TRACK2) {
                        ch = ch & 0x78;
                        ch = ch >>3;
                        csum = csum ^ ch;
                        dest[jj++]=ch+0x30;
                        itr++;
                        break;
                }
		/* Track 3 to be Tested */
                 else if ((ch & 0xf8) == SS2 && track == TRACK3) {
                        ch = ch & 0x78;
                        ch = ch >>3;
                        csum = csum ^ ch;
                        dest[jj++]=ch+0x30;
                        itr++;
                        break;
                }
        }
        if (itr >= cnt){
		//printk("1JJ=%d\n",jj) ;
                return -1;
        }
                                                                                                                             
        for (itr = itr, bits = 0; itr < cnt; itr++) {
                if (data[itr] > 0x1)
                        continue;
                bits++;
                ch = ch >> 1;
                if (data[itr] == 0x0)
                        ch = ch | 0x0;
                else
                        ch = ch | 0x80;
                if (bits == 0x7 && track == TRACK1) {
                        ch = ch >> 1;
                        if(chk_parity(ch) == 0x0){
                                return -1;
                        }
                        ch = ch & 0x3f;
                        csum = csum ^ ch;
                        dest[jj++] = ch  + 0x20;
                        if (dest[jj - 2] == ES1) {
                            	dest[jj] = '\0';
                                if(csum == 0) {
                                        return 0;
                                }
                                else{
                                        return -1;
                                }
                        }
                        bits = 0;
                        ch = 0;
                } else if (bits == 0x5 && track == TRACK2) {
                        ch = ch >> 3;
                        if(chk_parity(ch) == 0x0){
			//	printk ("Parity Track2\n") ;
                                return -1;
                        }
                        ch = ch & 0xf;
                        csum = csum ^ ch;
                        dest[jj++] = ch + 0x30;
                        if (dest[jj - 2] == ES2) {
                               	dest[jj] = '\0';
                                if(csum == 0) {
                                        return 0;
                                }
                                else{
			//		printk("5JJ=%d\n",jj) ;
                                        return -1;
                                }
                        }
                        bits = 0;
                        ch = 0;
                }
		/* Track 3 to be Tested */
                 else if (bits == 0x5 && track == TRACK3) {
                        ch = ch >> 3;
                        if(chk_parity(ch) == 0x0){
                                return -1;
                        }
                        ch = ch & 0xf;
                        csum = csum ^ ch;
                        dest[jj++] = ch + 0x30;
                        if (dest[jj - 2] == ES2) {
                             	dest[jj] = '\0';
                                if(csum == 0) {
                                        return 0;
                                }
                                else{
                                        return -1;
                                }
                        }
                        bits = 0;
                        ch = 0;
                }
        }
//	printk ("End Return\n") ;
        return -1;
}
/*--------------------------------------------------------------------------------------*/

/*-------------------------Parity checking ------------------------------------------------*/
static int chk_parity(unsigned char x)
{
        unsigned char pa;
        pa=x;
        pa^=pa >> 4;
        pa^=pa >> 2;
        pa^=pa >> 1;
        return (pa & 0x1);
}
/*--------------------------------------------------------------------------------------*/

/*-----------------------Process Reverse direction swipe data---------------------------*/
static int GetTrackDataRev(int *data, char *dest, int cnt, int track)
{
        int itr, bits, jj;
        unsigned char ch, csum;
        ch = 0;
        csum = 0; jj = 0;
                                                                                                                             
        for (itr = cnt; itr > 0; itr--) {
                if (data[itr] > 0x1)
                        continue;
                ch = ch >> 1;
                if (data[itr] == 0x0){
                        ch = ch | 0x0;
                }
                else{
                        ch = ch | 0x80;
                }
                                                                                                                             
                if ((ch & 0xfe) == SS1 && track == TRACK1) {
                        ch = ch & 0x7e;
                        ch= ch >>1;
                        csum = csum ^ ch;
                        dest[jj++]=ch+0x20;
                        itr--;
                        break;
                } else if ((ch & 0xf8) == SS2 && track == TRACK2) {
                        ch = ch & 0x78;
                        ch = ch >>3;
                        csum = csum ^ ch;
                        dest[jj++]=ch+0x30;
                        itr--;
                        break;
                }
                /* Track 3 to be Tested */ 
                else if ((ch & 0xf8) == SS2 && track == TRACK3) {
                        ch = ch & 0x78;
                        ch = ch >>3;
                        csum = csum ^ ch;
                        dest[jj++]=ch+0x30;
                        itr--;
                        break;
                }
        }
        if (itr >= cnt){
                return -1;
        }
                                                                                                                             
        for (itr = itr, bits = 0; itr > 0; itr--) {
                if (data[itr] > 0x1)
                        continue;
                bits++;
                ch = ch >> 1;
                                                                                                                             
                if (data[itr] == 0x0)
                        ch = ch | 0x0;
                else
                        ch = ch | 0x80;
                if (bits == 0x7 && track == TRACK1) {
                        ch = ch >> 1;
                        if(chk_parity(ch) == 0x0){
                                return -1;
                        }
                        ch = ch & 0x3f;
                        csum = csum ^ ch;
                        dest[jj++] = ch  + 0x20;
                        if (dest[jj - 2] == ES1) {
                              	dest[jj] = '\0';
                                if(csum == 0){
                                        return 0;
                                }
                                else{
                                        return -1;
                                }
                        }
                        bits = 0;
                        ch = 0;
                } else if (bits == 0x5 && track == TRACK2) {
                        ch = ch >> 3;
                        if(chk_parity(ch) == 0x0){
                                return -1;
                        }
                        ch = ch & 0xf;
                        csum = csum ^ ch;
                        dest[jj++] = ch + 0x30;
                        if (dest[jj - 2] == ES2) {
                               	dest[jj] = '\0';
                                if(csum == 0) {
                                        return 0;
                                }
                                else{
                                        return -1;
                                }
                        }
                        bits = 0;
                        ch = 0;
                }
		/* Track 3 to be Tested */
                 else if (bits == 0x5 && track == TRACK3) {
                        ch = ch >> 3;
                        if(chk_parity(ch) == 0x0){
                                return -1;
                        }
                        ch = ch & 0xf;
                        csum = csum ^ ch;
                        dest[jj++] = ch + 0x30;
                        if (dest[jj - 2] == ES2) {
                               	dest[jj] = '\0';
                                if(csum == 0) {
                                        return 0;
                                }
                                else{
                                        return -1;
                                }
                        }
                        bits = 0;
                        ch = 0;
                }
        }
        return -1;
}
/*--------------------------------------------------------------------------------------*/

/*--------------------------FILE OPERATIONS---------------------------------------------*/
                                                                                                                             
static struct file_operations mscrd_fops = {
        .owner          = THIS_MODULE,
        .llseek         = no_llseek,
        .read           = mscrd_read,
        .open           = mscrd_open,
        .release        = mscrd_close,
};
/*--------------------------------------------------------------------------------------*/

/*---------------------------Module Initialization---------------------------------------*/
static int __init mscrd_init(void)
{
        int result;
        int ret ;
	ready = 0;
        valid1 = 0;
        valid2 = 0;
        valid3 = 0;

	/* Register as a Char driver */
        result = register_chrdev(MAJORNO, "magswipe", &mscrd_fops);
        if (result < 0) {
                printk("device registration failed \n");
                return result ;
        }
	/* Setup GPIO Port pins */
        setup_port();
	/* Make required variables ready */
	makeready();
	/* Card load Interrupt request */
        ret = request_irq(card_load,card_load_interrupt,0,"card_load","magswipe") ;
        if (ret) {
                printk("Unable to register irq no %i \n", MS_CARD_LOAD);
                return ret;
        }
	/* Track1 Clock Interrupt request */
        ret = request_irq(clk1,clk1_interrupt,0,"track1_clk","magswipe") ;
        if (ret) {
                printk("Unable to register irq no %i \n", MS_TRACK1_CLK);
                return ret;
        }
	/* Track2 Clock Interrupt request */
        ret = request_irq(clk2,clk2_interrupt,0,"track2_clk","magswipe") ;
        if (ret) {
                printk("Unable to register irq no %i \n", MS_TRACK2_CLK);
                return ret;
        }
	/* Track3 Clock Interrupt request */
        ret = request_irq(clk3,clk3_interrupt,0,"track3_clk","magswipe") ;
        if (ret) {
                printk("Unable to register irq no %i \n", MS_TRACK3_CLK);
                return ret;
        } 
	cleanup_port() ;

        return 0;
}
/*--------------------------------------------------------------------------------------*/

/*---------------------------Module Exit------------------------------------------------*/
static void __exit mscrd_exit(void)
{
        free_irq(card_load,"magswipe") ;
        free_irq(clk1,"magswipe") ;
        free_irq(clk2,"magswipe") ;
        free_irq(clk3,"magswipe") ;


        gpio_free(MS_CARD_LOAD);
        gpio_free(MS_TRACK1_CLK);
        gpio_free(MS_TRACK1_DATA);
        gpio_free(MS_TRACK2_CLK);
        gpio_free(MS_TRACK2_DATA);
        gpio_free(MS_TRACK3_CLK);
        gpio_free(MS_TRACK3_DATA);

	/* unregister char device driver */
        unregister_chrdev(MAJORNO,"magswipe");
}
/*--------------------------------------------------------------------------------------*/

module_init(mscrd_init);
module_exit(mscrd_exit);
                                                                                                                             
MODULE_DESCRIPTION("magnetic swipe card reader driver");
MODULE_AUTHOR("malleswari@visiontek.co.in");
MODULE_LICENSE("GPL");

