#include<linux/init.h>
#include <linux/compiler.h> /* __must_check */
#include <linux/fs.h> 	     /* file stuff */
#include <linux/kernel.h>    /* printk() */
#include <linux/errno.h>     /* error codes */
#include <linux/module.h>  /* THIS_MODULE */
#include <linux/cdev.h>      /* char device stuff */
#include <asm/uaccess.h>  /* copy_to_user() */
#include <linux/fs.h>		/* for register_chardev, file_operations  etc. */
#include <linux/version.h>
#define NAME "naresh"
int result;
static const char    g_s_Hello_World_string[] = "naresh world from kernel mode!\n\0";
static const ssize_t g_s_Hello_World_size = sizeof(g_s_Hello_World_string);

static ssize_t device_file_read( struct file *file_ptr , char __user *user_buffer , size_t count, loff_t *possition)
{
	printk( KERN_NOTICE "driver: Device file is read at offset = %i, read bytes count = %u"
			, (int)*possition
			, (unsigned int)count );

	if( *possition >= g_s_Hello_World_size )
		return 0;

	if( *possition + count > g_s_Hello_World_size )
		count = g_s_Hello_World_size - *possition;

	if( copy_to_user(user_buffer, g_s_Hello_World_string + *possition, count) != 0 )
	return -EFAULT;   

	*possition += count;
	return count;
}
/*===============================================================================================*/
static struct file_operations fops = 
{
	.owner   = THIS_MODULE,
	.read    = device_file_read,
};
static int hello_init(void)
{


	result = register_chrdev(0, NAME,&fops);
	if (result < 0)
	{
		printk(KERN_ALERT"<1> device registration failed");
	}
	printk(KERN_ALERT" Naresh World Major number= %d ",(int)result);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_NOTICE" Bye naresh world");
	unregister_chrdev(result, NAME);
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("R&d");
MODULE_AUTHOR("naresh");
