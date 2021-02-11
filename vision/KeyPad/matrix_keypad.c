/*
 *  GPIO driven matrix keyboard driver
 *
 *  Copyright (c) 2008 Marek Vasut <marek.vasut@gmail.com>
 *
 *  Based on corgikbd.c
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 */
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/jiffies.h>
#include <linux/module.h>
#include <linux/slab.h>

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

#include <linux/input/matrix_keypad.h>

#include <linux/gfp.h>
#include <linux/percpu.h>
#include <linux/kmod.h>
#include <linux/kernel_stat.h>
#include <linux/workqueue.h>



/* ****************** Hardware pins of GL11 POS **************** */
#define MX6_BRD_LCD_DAT8_ROW0        IMX_GPIO_NR(3, 25) 
#define MX6_BRD_LCD_DAT9_ROW1        IMX_GPIO_NR(3, 27) 
#define MX6_BRD_LCD_DAT10_ROW2       IMX_GPIO_NR(3, 29) 
#define MX6_BRD_LCD_DAT11_COL0       IMX_GPIO_NR(3, 24) 
#define MX6_BRD_LCD_DAT12_COL1       IMX_GPIO_NR(3, 26) 
#define MX6_BRD_LCD_DAT13_COL2       IMX_GPIO_NR(3, 28) 
#define MX6_BRD_LCD_DAT14_KBINT      IMX_GPIO_NR(4, 1) 
#define MX6_BRD_LCD_BACKLIGHT        IMX_GPIO_NR(3, 23)
#define MX6_BRD_KP_BUZZER            IMX_GPIO_NR(3, 7)
#define MX6_BRD_KP_BACKLIGHT         IMX_GPIO_NR(1, 28)


#define col_get_gpio_value(gpio_pin)   	gpio_get_value(gpio_pin)
#define encoder_gs()                  	gpio_get_value(MX6_BRD_LCD_DAT14_KBINT)
/* **************************************************************** */

#define DEBUG 1
struct matrix_keypad {
	const struct matrix_keypad_platform_data *pdata;
	struct input_dev *input_dev;
	struct timer_list timer;
	unsigned short *keycodes;
	unsigned int row_shift;

	uint32_t last_key_state[MATRIX_MAX_COLS];
	bool scan_pending;
	bool stopped;
	spinlock_t lock;
};

static struct timer_list bkl_timer ;
//volatile int backlight_timeout =0;
//EXPORT_SYMBOL(backlight_timeout);

volatile int key_buzzer_onoff_flag =1;
EXPORT_SYMBOL(key_buzzer_onoff_flag);

volatile int touch_buzzer_onoff_flag =1;
EXPORT_SYMBOL(touch_buzzer_onoff_flag);

volatile unsigned char bkl_off_flag = 1 ;

static volatile int rowdata = 0  ;
static volatile char scan_count = 0  ;
static volatile char enter_count = 0  ;
static volatile char shift_count = 0  ;
static volatile char fn_key_count = 0  ;
static volatile char default_keys = 0  ;
static volatile char clear_count = 0  ;

volatile char key_out_flag = 0 ;
EXPORT_SYMBOL(key_out_flag);

//static void bkl_controller(void);
//static void bkl_timedout (unsigned long arg) ;


/*

   static void bkl_timedout (unsigned long arg)
   {
   if(bkl_off_flag==0)
   bkl_off_flag = 1 ;
   gpio_set_value(MX6_BRD_LCD_BACKLIGHT,0);
   gpio_set_value(MX6_BRD_KP_BACKLIGHT,0);
   }
   */

#if 0

void bkl_controller(void)
{
	gpio_set_value(MX6_BRD_LCD_BACKLIGHT,1);
	gpio_set_value(MX6_BRD_KP_BACKLIGHT,1);
	if(bkl_off_flag==1)
		bkl_off_flag = 0 ;
	if(key_buzzer_onoff_flag)
		gpio_set_value(MX6_BRD_KP_BUZZER,1);
	if (backlight_timeout > 90)
		backlight_timeout = 90 ;
	else if (backlight_timeout < 16)
		backlight_timeout = 16 ;

	mod_timer(&bkl_timer,(jiffies+(HZ*backlight_timeout))) ;
	mdelay(10) ;
	gpio_set_value(MX6_BRD_KP_BUZZER,0);

}
EXPORT_SYMBOL(bkl_controller);

void touch_bkl_controller(void)
{
	gpio_set_value(MX6_BRD_LCD_BACKLIGHT,1);
	gpio_set_value(MX6_BRD_KP_BACKLIGHT,1);
	if(bkl_off_flag==1)
		bkl_off_flag = 0 ;
	if(touch_buzzer_onoff_flag)
		gpio_set_value(MX6_BRD_KP_BUZZER,1);
	if (backlight_timeout > 90)
		backlight_timeout = 90 ;
	else if (backlight_timeout < 16)
		backlight_timeout = 16 ;

	mod_timer(&bkl_timer,(jiffies+(HZ*backlight_timeout))) ;
	mdelay(10) ;
	gpio_set_value(MX6_BRD_KP_BUZZER,0);

}

EXPORT_SYMBOL(touch_bkl_controller);
#endif


static void kpad_timer(unsigned long data)
{
	struct platform_device *pdev =  (struct platform_device *) data;
	struct matrix_keypad *keypad = platform_get_drvdata(pdev);
	uint32_t new_state[MATRIX_MAX_COLS];
	struct input_dev *input_dev = keypad->input_dev;
	int i = 0 , code , val = 0;

#ifdef DEBUG
	//	printk("%s %d encoder_gs() = %d\n",__func__,__LINE__,encoder_gs() );
#endif

	memset(new_state, 0, sizeof(new_state));
	if(encoder_gs() == 0 )
	{
		if(scan_count)
		{
			val = col_get_gpio_value(MX6_BRD_LCD_DAT11_COL0);
			new_state[rowdata] = val ;
			val = col_get_gpio_value(MX6_BRD_LCD_DAT12_COL1);
			if(val)
				new_state[rowdata] |= 0x02 ;
			val = col_get_gpio_value(MX6_BRD_LCD_DAT13_COL2);
			if(val)
				new_state[rowdata] |= 0x04 ;
			if((new_state[rowdata] == 5) && (rowdata == 3) ){ // ( KEY( Col, Row );
				if(fn_key_count == 1)		
					fn_key_count = 0 ;
				shift_count ++ ;
				if(shift_count == 1){
					code = MATRIX_SCAN_CODE((new_state[rowdata]), rowdata, keypad->row_shift);
					//input_event(input_dev, EV_MSC, MSC_SCAN, code);
					pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],1);
					//bkl_controller();
					//input_sync(input_dev) ;
					scan_count = 0 ;
				}
				else if (shift_count == 2){
					code = MATRIX_SCAN_CODE((new_state[rowdata]), rowdata, keypad->row_shift);
					//input_event(input_dev, EV_MSC, MSC_SCAN, code);
					pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],0);
					//input_sync(input_dev) ;
					shift_count = 0 ;
					scan_count = 0 ;
				}
				//bkl_controller() ;
				key_out_flag=1;
				//printk(" printk key4\n");
			}
			else if((rowdata == 6) && (new_state[rowdata] == 4)){
				fn_key_count ++ ;
				if(fn_key_count == 1){
					scan_count = 0 ;
				}
				else if(fn_key_count == 2){
					scan_count = 0 ;
					fn_key_count = 0 ;
				}
				//bkl_controller() ;
				key_out_flag=1;
			}
			else
			{		// row,col,key  0 1 0 2 
				/*KEY(0, 0, KEY_Q),KEY(0, 1, KEY_I),KEY(0, 2, KEY_G),KEY(0, 3, KEY_C),KEY(0, 4, KEY_TAB),KEY(0, 5, KEY_4),KEY(0, 6, KEY_8),KEY(0, 7, KEY_ENTER),
				  KEY(1, 0, KEY_W),KEY(1, 1, KEY_O),KEY(1, 2, KEY_H),KEY(1, 3, KEY_V),KEY(1, 4, KEY_1),KEY(1, 5, KEY_5),KEY(1, 6, KEY_9),KEY(1, 7, KEY_RESERVED),
				  KEY(2, 0, KEY_E),KEY(2, 1, KEY_P),KEY(2, 2, KEY_J),KEY(2, 3, KEY_B),KEY(2, 4, KEY_2),KEY(2, 5, KEY_6),KEY(2, 6, KEY_RIGHT),KEY(2, 7,KEY_RESERVED),
				  KEY(3, 0, KEY_R),KEY(3, 1, KEY_A),KEY(3, 2, KEY_K),KEY(3, 3, KEY_N),KEY(3, 4, KEY_3),KEY(3, 5, KEY_BACKSPACE),KEY(3, 6, KEY_END),KEY(3, 7, KEY_RESERVED),
				  KEY(4, 0, KEY_T),KEY(4, 1, KEY_S),KEY(4, 2, KEY_L),KEY(4, 3, KEY_M),KEY(4, 4, KEY_ESC),KEY(4, 5, KEY_LEFT),KEY(4, 6, KEY_RESERVED),KEY(4, 7, KEY_RESERVED),
				  KEY(5, 0, KEY_Y),KEY(5, 1, KEY_D),KEY(5, 2, KEY_Z),KEY(5, 3, KEY_RIGHTSHIFT),KEY(5, 4, KEY_DOWN),KEY(5, 5, KEY_HOME),KEY(5, 6, KEY_0),KEY(5, 7, KEY_RESERVED),
				  KEY(6, 0, KEY_U),KEY(6, 1, KEY_F),KEY(6, 2, KEY_X),KEY(6, 3, KEY_UP),KEY(6, 4, KEY_INSERT),KEY(6, 5, KEY_7),KEY(6, 6, KEY_SPACE),KEY(6, 7, KEY_RESERVED), KEY(7, 0, KEY_MINUS) 
				//if(	(new_state[rowdata] == 6 && rowdata == 3) // KEY_UP
				// || (new_state[rowdata] == 5 && rowdata == 4) //KEY_LEFT
				// || (new_state[rowdata] == 4 && rowdata == 5) //KEY_DOWN
				// ||(new_state[rowdata] == 2 && rowdata == 6) // KEY_X
				// ||(new_state[rowdata] == 0 && rowdata == 4) // KEY_TAB
				// ||(new_state[rowdata] == 6 && rowdata == 4) // KEY_RESERVED
				// ||(new_state[rowdata] == 5 && rowdata == 5) // KEY_HOME
				// ||(new_state[rowdata] == 3 && rowdata == 6) // KEY_UP
				// ||(new_state[rowdata] == 4 && rowdata == 4) // KEY_ESC
				// ||(new_state[rowdata] == 3 && rowdata == 5) // KEY_RIGHTSHIFT
				// ||(new_state[rowdata] == 0 && rowdata == 7) // KEY_MINUS
				// ||(new_state[rowdata] == 6 && rowdata == 6)) //KEY_SPACE */
				if(	(new_state[rowdata] == 6 && rowdata == 3) || (new_state[rowdata] == 5 && rowdata == 4)|| (new_state[rowdata] == 4 && rowdata == 5)||(new_state[rowdata] == 2 && rowdata == 6)||(new_state[rowdata] == 0 && rowdata == 4)||(new_state[rowdata] == 6 && rowdata == 4)||(new_state[rowdata] == 5 && rowdata == 5)||(new_state[rowdata] == 3 && rowdata == 6)||(new_state[rowdata] == 4 && rowdata == 4)||(new_state[rowdata] == 3 && rowdata == 5)||(new_state[rowdata] == 0 && rowdata == 7)||(new_state[rowdata] == 6 && rowdata == 6))
					default_keys = 1 ;



				// If function Key == 1 + No Default Keys  
				if((fn_key_count == 1) && (default_keys != 1))
				{
					if(shift_count == 1){
						code = MATRIX_SCAN_CODE(5, 3, keypad->row_shift);
						//input_event(input_dev, EV_MSC, MSC_SCAN, code);
						pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],0);
						//input_sync(input_dev) ;
						shift_count = 0 ;
					}
					if(((new_state[rowdata]) % 2) == 0){ // Even Coloumn 
						// Q   , 
						code = MATRIX_SCAN_CODE((new_state[rowdata]+7), rowdata, keypad->row_shift);
						//input_event(input_dev, EV_MSC, MSC_SCAN, code);
						pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],1);
						//bkl_controller();
						//input_sync(input_dev) ;
						udelay(1) ;
						//input_event(input_dev, EV_MSC, MSC_SCAN, code);
						pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],0);
						//input_sync(input_dev) ;
						scan_count = 0 ;
						//printk(" printk key1\n");
						//bkl_controller() ;
						key_out_flag=1;
					}
					else {
						code = MATRIX_SCAN_CODE(5, 3, keypad->row_shift);
						//input_event(input_dev, EV_MSC, MSC_SCAN, code);
						pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],1);
						//bkl_controller();
						//input_sync(input_dev) ;
						udelay(1) ;

						code = MATRIX_SCAN_CODE((new_state[rowdata]+7), rowdata, keypad->row_shift);
						//input_event(input_dev, EV_MSC, MSC_SCAN, code);
						pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],1);
						//input_sync(input_dev) ;
						udelay(1) ;
						//input_event(input_dev, EV_MSC, MSC_SCAN, code);
						pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],0);
						//input_sync(input_dev) ;

						code = MATRIX_SCAN_CODE(5, 3, keypad->row_shift);
						//input_event(input_dev, EV_MSC, MSC_SCAN, code);
						pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],0);
						//input_sync(input_dev) ;
						scan_count = 0 ;
						//printk(" printk key3\n");
						//bkl_controller() ;
						key_out_flag=1;
					}
				}
				else
				{

					// Function ( Pressed or Not ) + Default Must Press 
					if((fn_key_count == 1)&& (default_keys == 1))
					{
						if(shift_count == 1){  // Case For KEY_RIGHTSHIFT

							code = MATRIX_SCAN_CODE(5, 3, keypad->row_shift);
							//input_event(input_dev, EV_MSC, MSC_SCAN, code);
							pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],0);
							//input_sync(input_dev) ;
							shift_count = 0 ;
						}
					}
					code = MATRIX_SCAN_CODE((new_state[rowdata]), rowdata, keypad->row_shift);
					//input_event(input_dev, EV_MSC, MSC_SCAN, code);
					pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],1);
					//bkl_controller();
					//input_sync(input_dev) ;
					udelay(3) ;
					//input_event(input_dev, EV_MSC, MSC_SCAN, code);
					pr_info("keypad->keycodes[code] = %d\n",keypad->keycodes[code]);input_report_key(input_dev,keypad->keycodes[code],0);
					//input_sync(input_dev) ;
					scan_count = 0 ;
					default_keys = 0 ;
					//printk(" printk key2\n");
					//bkl_controller) ;
					key_out_flag=1;
					if((new_state[rowdata] == 3 && rowdata == 5)){
						clear_count ++ ;
					}
				}
			}
			if(rowdata ==7){
				scan_count = 0 ;
				rowdata = 0 ;
			}
		}
		else if(rowdata == 7){
			if(enter_count){
				scan_count ++ ;
				enter_count = 0 ;
			}
			else
				enter_count ++ ;
		}
		else if(clear_count){
			if(clear_count == 2){
				scan_count ++ ;
				clear_count = 0 ;
			}
			clear_count ++ ;
		}
	}
	else{
		clear_count = 0 ;

		for(i=0;i<8;i++)
		{
			if(i == 7){
				rowdata =7;
				gpio_set_value(MX6_BRD_LCD_DAT8_ROW0,1);
				gpio_set_value(MX6_BRD_LCD_DAT9_ROW1,1);
				gpio_set_value(MX6_BRD_LCD_DAT10_ROW2,1);
			}
			else {
				rowdata =0;
				gpio_set_value(MX6_BRD_LCD_DAT8_ROW0,0);
				gpio_set_value(MX6_BRD_LCD_DAT9_ROW1,0);
				gpio_set_value(MX6_BRD_LCD_DAT10_ROW2,0);

				rowdata = i;
				if((i & 0x1))
					gpio_set_value(MX6_BRD_LCD_DAT8_ROW0,1);
				if(i & 0x2)
					gpio_set_value(MX6_BRD_LCD_DAT9_ROW1,1);
				if(i & 0x4)
					gpio_set_value(MX6_BRD_LCD_DAT10_ROW2,1);
			}
			if(encoder_gs() == 0 )
			{
				scan_count ++ ;
				break ;
			}	
		}
	}
	mod_timer(&keypad->timer,(jiffies + 5)) ;
}	

static int matrix_keypad_start(struct input_dev *dev)
{
	struct matrix_keypad *keypad = input_get_drvdata(dev);

#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif

	scan_count = 0 ;
	enter_count = 0 ;
	shift_count = 0 ;
	fn_key_count = 0 ;	
	default_keys = 0 ;
	clear_count = 0 ;

	keypad->stopped = false;
	mb();

/* Mandatory barriers are used to enforce memory consistency on a full system level. The most common example of this is when communicating with external memory mapped peripherals. All mandatory barriers are guaranteed to expand to at least a compiler barrier, regardless of target architecture.     
Statement 	Description

mb()

	A full system memory barrier. All memory operations before the mb() in the instruction stream will be committed before any operations after the mb() are committed. This ordering will be visible to all bus masters in the system. It will also ensure the order in which accesses from a single processor reaches slave devices.

rmb()

	Like mb(), but only guarantees ordering between read accesses. That is, all read operations before an rmb() will be committed before any read operations after the rmb().

wmb()

	Like mb(), but only guarantees ordering between write accesses. That is, all write operations before a wmb() will be committed before any write operations after the wmb(). */
	return 0;
}

static void matrix_keypad_stop(struct input_dev *dev)
{
	struct matrix_keypad *keypad = input_get_drvdata(dev);

#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif
	scan_count = 0 ;
	enter_count = 0 ;
	shift_count = 0 ;
	fn_key_count = 0 ;	
	default_keys = 0 ;
	clear_count = 0 ;

	keypad->stopped = true;
	mb();
}

#ifdef CONFIG_PM
static int matrix_keypad_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct matrix_keypad *keypad = platform_get_drvdata(pdev);
	const struct matrix_keypad_platform_data *pdata = keypad->pdata;
	int i;

#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif

	matrix_keypad_stop(keypad->input_dev);

	if (device_may_wakeup(&pdev->dev))
		for (i = 0; i < pdata->num_row_gpios; i++)
			enable_irq_wake(gpio_to_irq(pdata->row_gpios[i]));

	return 0;
}

static int matrix_keypad_resume(struct platform_device *pdev)
{
	struct matrix_keypad *keypad = platform_get_drvdata(pdev);
	const struct matrix_keypad_platform_data *pdata = keypad->pdata;
	int i;


#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif

	if (device_may_wakeup(&pdev->dev))
		for (i = 0; i < pdata->num_row_gpios; i++)
			disable_irq_wake(gpio_to_irq(pdata->row_gpios[i]));

	matrix_keypad_start(keypad->input_dev);

	return 0;
}
#else
#define matrix_keypad_suspend	NULL
#define matrix_keypad_resume	NULL
#endif

static int __devinit init_matrix_gpio(struct platform_device *pdev,
		struct matrix_keypad *keypad)
{

#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_ROW0__GPIO_3_25) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_ROW1__GPIO_3_27) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_ROW2__GPIO_3_29) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_COL0__GPIO_3_24) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_COL1__GPIO_3_26) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_COL2__GPIO_3_28) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_ROW4__GPIO_4_1) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_PWM1__GPIO_3_23) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_SDCE1__GPIO_1_28) ;
	mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT19__GPIO_3_7) ;

	gpio_request(MX6_BRD_LCD_DAT8_ROW0,"mrow0") ;
	gpio_request(MX6_BRD_LCD_DAT9_ROW1,"mrow1") ;
	gpio_request(MX6_BRD_LCD_DAT10_ROW2,"mrow2") ;
	gpio_request(MX6_BRD_LCD_DAT11_COL0,"mcol0") ;
	gpio_request(MX6_BRD_LCD_DAT12_COL1,"mcol1") ;
	gpio_request(MX6_BRD_LCD_DAT13_COL2,"mcol2") ;
	gpio_request(MX6_BRD_LCD_DAT14_KBINT,"mkbint") ;
	gpio_request(MX6_BRD_LCD_BACKLIGHT,"lcdbacklight") ;
	gpio_request(MX6_BRD_KP_BUZZER,"kpbuzzer") ;
	gpio_request(MX6_BRD_KP_BACKLIGHT,"kpbacklight") ;

	gpio_direction_output(MX6_BRD_LCD_DAT8_ROW0, 0);
	gpio_direction_output(MX6_BRD_LCD_DAT9_ROW1, 0);
	gpio_direction_output(MX6_BRD_LCD_DAT10_ROW2, 0);
	gpio_direction_output(MX6_BRD_LCD_BACKLIGHT, 0);
	gpio_direction_output(MX6_BRD_KP_BUZZER, 0);
	gpio_direction_output(MX6_BRD_KP_BACKLIGHT, 0);
	gpio_direction_input(MX6_BRD_LCD_DAT11_COL0);
	gpio_direction_input(MX6_BRD_LCD_DAT12_COL1);
	gpio_direction_input(MX6_BRD_LCD_DAT13_COL2);
	gpio_direction_input(MX6_BRD_LCD_DAT14_KBINT);

	return 0;
}

static int __devinit matrix_keypad_probe(struct platform_device *pdev)
{
	const struct matrix_keypad_platform_data *pdata;
	const struct matrix_keymap_data *keymap_data;
	struct matrix_keypad *keypad;
	struct input_dev *input_dev;
	unsigned short *keycodes;
	unsigned int row_shift;
	int i;
	int err;


#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif

	pdata = pdev->dev.platform_data;
	if (!pdata) {
		dev_err(&pdev->dev, "no platform data defined\n");
		return -EINVAL;
	}

	keymap_data = pdata->keymap_data;
	if (!keymap_data) {
		dev_err(&pdev->dev, "no keymap data defined\n");
		return -EINVAL;
	}

	row_shift = 3 ;

	keypad = kzalloc(sizeof(struct matrix_keypad), GFP_KERNEL);
	keycodes = kzalloc((14 << row_shift) *
			sizeof(*keycodes),
			GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!keypad || !keycodes || !input_dev) {
		err = -ENOMEM;
		goto err_free_mem;
	}

	keypad->input_dev = input_dev;
	keypad->pdata = pdata;
	keypad->keycodes = keycodes;
	keypad->row_shift = row_shift;
	keypad->stopped = true;
	spin_lock_init(&keypad->lock);

	input_dev->name		= pdev->name;
	input_dev->id.bustype	= BUS_HOST;
	input_dev->dev.parent	= &pdev->dev;
	input_dev->evbit[0]	= BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	input_dev->open		= matrix_keypad_start;
	input_dev->close	= matrix_keypad_stop;

	input_dev->keycode	= keycodes;
	input_dev->keycodesize	= sizeof(*keycodes);
	input_dev->keycodemax	= pdata->num_row_gpios << keypad->row_shift;

	for (i = 0; i < keymap_data->keymap_size; i++) {
		unsigned int key = keymap_data->keymap[i];
		unsigned int row = KEY_ROW(key);
		unsigned int col = KEY_COL(key);
		unsigned short code = KEY_VAL(key);

		keycodes[MATRIX_SCAN_CODE(row, col, row_shift)] = code;
		printk ("row = %d\tcol = %d\tcode = %d\tkeycode[i] = %d\t\ti = %d\tkey = %d \n",row,col,code,keycodes[i],i,key) ;
		__set_bit(code, input_dev->keybit);
	}
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	input_set_capability(input_dev, EV_MSC, MSC_SCAN); // 
	input_set_drvdata(input_dev, keypad);

	err = init_matrix_gpio(pdev, keypad);
	if (err)
		goto err_free_mem;

	err = input_register_device(keypad->input_dev);
	if (err)
		goto err_free_mem;

	/*
	   init_timer (&bkl_timer) ;
	   bkl_timer.function = bkl_timedout ;
	   bkl_timer.expires = jiffies + 1 ;
	   backlight_timeout = 16 ;
	   */
	pr_info(" P Column0 = %d\n", col_get_gpio_value(MX6_BRD_LCD_DAT11_COL0));
	pr_info(" P Column1 = %d\n", col_get_gpio_value(MX6_BRD_LCD_DAT12_COL1));
	pr_info("  P Column2 = %d\n", col_get_gpio_value(MX6_BRD_LCD_DAT13_COL2));


	setup_timer(&keypad->timer, kpad_timer, (unsigned long) pdev);
	mod_timer(&keypad->timer, jiffies + 5) ;	
	device_init_wakeup(&pdev->dev, pdata->wakeup);
	platform_set_drvdata(pdev, keypad);

	return 0;

err_free_mem:
	input_free_device(input_dev);
	kfree(keycodes);
	kfree(keypad);
	return err;
}

static int __devexit matrix_keypad_remove(struct platform_device *pdev)
{
	struct matrix_keypad *keypad = platform_get_drvdata(pdev);
	const struct matrix_keypad_platform_data *pdata = keypad->pdata;
	int i;

#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif

	device_init_wakeup(&pdev->dev, 0);

	for (i = 0; i < pdata->num_row_gpios; i++) {
		gpio_free(pdata->row_gpios[i]);
	}

	for (i = 0; i < pdata->num_col_gpios; i++)
		gpio_free(pdata->col_gpios[i]);

	del_timer_sync(&keypad->timer);
	input_unregister_device(keypad->input_dev);
	platform_set_drvdata(pdev, NULL);
	kfree(keypad->keycodes);
	kfree(keypad);
	del_timer(&bkl_timer);

	return 0;
}

static struct platform_driver matrix_keypad_driver = {
	.probe		= matrix_keypad_probe,
	.remove		= __devexit_p(matrix_keypad_remove),
	.suspend	= matrix_keypad_suspend,
	.resume		= matrix_keypad_resume,
	.driver		= {
		.name	= "matrix-keypad",
		.owner	= THIS_MODULE,
	},
};

static int __init matrix_keypad_init(void)
{
#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif

	return platform_driver_register(&matrix_keypad_driver);
}

static void __exit matrix_keypad_exit(void)
{

#ifdef DEBUG
	printk("%s %d\n",__func__,__LINE__);
#endif

	platform_driver_unregister(&matrix_keypad_driver);
}

module_init(matrix_keypad_init);
module_exit(matrix_keypad_exit);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("GPIO Driven Matrix Keypad Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:matrix-keypad");

