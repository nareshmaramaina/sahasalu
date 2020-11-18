#include <linux/module.h>
 
#include <linux/errno.h>
 
#include <linux/kernel.h>
 
#include <linux/device.h>
 
#include <linux/kdev_t.h>
 
#include <linux/err.h>
 
MODULE_AUTHOR("my name");
 
MODULE_LICENSE("Dual BSD/GPL");
 
static int major_i=120;
 
static int minor_i=0;
 
struct class* mclass;
 
static int node_init(void)
 
{
 
     /*class_create creates a noddev folder in /sys/class*/    
 
  mclass=class_create(THIS_MODULE,"noddev");
 
  if(IS_ERR(mclass))
 
  {
 
    printk(KERN_ALERT "fail to create class\n");
 
    return -1;
 
  }  
 
     /*class_device_create Create noddev0 device under /dev*/
 
  device_create(mclass,NULL,MKDEV(major_i,minor_i),NULL,"noddev0");  
 
     /*The last parameter here can be formatted with const char *fmt, ...*/
 
  device_create(mclass,NULL,MKDEV(major_i,minor_i+20),NULL,"noddev%d",minor_i+20);
 
  printk(KERN_ALERT "create node success:\n");
 
  printk(KERN_ALERT "  ls -l /dev/noddev*\n");
 
  printk(KERN_ALERT "  ls -l /sys/class/noddev\n");
 
  return 0;
 
}
 
 
 
static void node_exit(void)
 
{    
 
 
  device_destroy(mclass,MKDEV(major_i,minor_i));
 
  device_destroy(mclass,MKDEV(major_i,minor_i+20)); 
 
     class_destroy(mclass); /*delete class*/
 
  printk(KERN_ALERT "goodbye\n");
 
}
 
module_init(node_init);
 
module_exit(node_exit);
