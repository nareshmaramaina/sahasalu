#include <linux/compiler.h> /* __must_check */
#include <linux/fs.h> 	     /* file stuff */
#include <linux/kernel.h>    /* printk() */
#include <linux/errno.h>     /* error codes */
#include <linux/module.h>  /* THIS_MODULE */
#include <linux/cdev.h>      /* char device stuff */
#include <asm/uaccess.h>  /* copy_to_user() */
#include <linux/init.h>       /* module_init, module_exit */
#include <linux/module.h> /* version info, MODULE_LICENSE, MODULE_AUTHOR, printk() */
static const char    g_s_Hello_World_string[] = "Hello world from kernel mode!\n\0";
static const ssize_t g_s_Hello_World_size = sizeof(g_s_Hello_World_string);
int register_device(void); /* 0 if Ok*/
void 			 unregister_device(void); 

/*===============================================================================================*/
static int simple_driver_init(void)
{
      int result = 0;
    printk( KERN_NOTICE "Simple-driver: Initialization started" );

      result = register_device();

    return result;
}
/*-----------------------------------------------------------------------------------------------*/
static void simple_driver_exit(void)
{
   printk( KERN_NOTICE "Simple-driver: Exiting" );
    unregister_device();
}
/*===============================================================================================*/

module_init(simple_driver_init);
module_exit(simple_driver_exit);

/*===============================================================================================*/
static ssize_t device_file_read(
                           struct file *file_ptr
                        , char __user *user_buffer
                        , size_t count
                        , loff_t *possition)
{
   printk( KERN_NOTICE "Simple-driver: Device file is read at offset = %i, read bytes count = %u"
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
static struct file_operations simple_driver_fops = 
{
   .owner   = THIS_MODULE,
   .read    = device_file_read,
};

static int device_file_major_number = 0;

static const char device_name[] = "Simple-driver";

/*===============================================================================================*/
int register_device(void)
{
      int result = 0;

      printk( KERN_NOTICE "Simple-driver: register_device() is called." );

      result = register_chrdev( 0, device_name, &simple_driver_fops );
      if( result < 0 )
      {
         printk( KERN_WARNING "Simple-driver:  can\'t register character device with errorcode = %i", result );
         return result;
      }

      device_file_major_number = result;
      printk( KERN_NOTICE "Simple-driver: registered character device with major number = %i and minor numbers 0...255"
                  , device_file_major_number );

      return 0;
}
/*-----------------------------------------------------------------------------------------------*/
void unregister_device(void)
{
   printk( KERN_NOTICE "Simple-driver: unregister_device() is called" );
   if(device_file_major_number != 0)
   {
      unregister_chrdev(device_file_major_number, device_name);
   }
}
MODULE_LICENSE("R&d");
MODULE_AUTHOR("naresh");
