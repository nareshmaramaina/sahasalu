/* Implementation of device Driver for RTC, check Reamme.clock for 
details on our design.
Version : 1.0
Author : Team - C.
*/
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/fs.h>    
#include <linux/slab.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <linux/init.h>
#include <asm/uaccess.h> //copy_from/to_user
#include "clock.h"


static unsigned char inuse = 0; 

unsigned char cmd_arr[]={
	DAY_CMD,
	MONTH_CMD,
	YEAR_CMD,
	HOURS_CMD,
	MINUTES_CMD,
	SECONDS_CMD
	};
/* above array is used to simplify writing code for read/write according
to the design as described in Readme.clock.
*/


/* we will allow only one app to access RTC at a point of time. */

int rtc_open(struct inode *inode, struct file *filp)
{
	if(inuse)
		return -EBUSY;
	inuse = 1;// indicating this is in use.
	return 0;
}

int rtc_release(struct inode *inode, struct file *filp)
{
	inuse = 0;
	return 0;
}

/* Limitation : can write only one byte at a point of time,can extend 
   this by slightly modifying the code . We leave this as exercise
   for students */

ssize_t rtc_write(struct file *filp, const char *buf, size_t count,
		    loff_t *f_pos)
{
	unsigned char cmd,data;
	if(count > 1)
		return -EIO; // IO error.
	if(*f_pos >= FILE_SIZE)
		return -EIO; // IO error.
	cmd = cmd_arr[*f_pos];
	if( copy_from_user(&data,buf,1))
		return -EFAULT;
	printk("cmd = %d  data = %d\n",cmd,data);
	WRITE_TO_CLOCK(cmd,data);		
	(*f_pos)++;
	return 1;
}

ssize_t rtc_read(struct file *filp,char *buf, size_t count,
		    loff_t *f_pos)
{
	unsigned char cmd=0,data=0;
	data=0;
	if(count > 1)
		return -EIO; // IO error.
	if(*f_pos >= FILE_SIZE)
		return -EIO; // IO error.
	cmd = cmd_arr[*f_pos];
	READ_FROM_CLOCK(cmd,data);
	if (copy_to_user(buf,&data,1))
		return -EFAULT;
	printk("data = %d cmd = %d \n",data,cmd);
	(*f_pos)++;
	return 1;
}
struct file_operations fops = {
	write: rtc_write,
 	read: rtc_read,
	open: rtc_open,
	release: rtc_release
};

int init_module(void)
{
	int result = 0;
	inuse = 0;
	result = register_chrdev(CLOCK_MAJOR,"clock",&fops);
	return 0;
}

void cleanup_module(void)
{
    unregister_chrdev(CLOCK_MAJOR, "clock");
}
 

