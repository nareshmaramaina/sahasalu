#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include<linux/sysfs.h> 
#include<linux/kobject.h> 
#include<linux/sysfs.h>
#include<linux/kobject.h>
struct kobject *k_ref;
volatile int etx_value = 0;
static ssize_t sysfs_show(struct kobject *kobj,
                struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d", etx_value);
}

static ssize_t sysfs_store(struct kobject *kobj,
                struct kobj_attribute *attr,const char *buf, size_t count)
{
        sscanf(buf,"%d",&etx_value);
        return count;
}

struct kobj_attribute etx_attr = __ATTR(etx_value, 0644, sysfs_show, sysfs_store);

//struct kobj_attribute etx_attr = __ATTR(etx_value, 0660, sysfs_show, sysfs_store);

//This Function will be called from Init function
/*Creating a directory in /sys/kernel/ */
//kobj_ref = kobject_create_and_add("etx_sysfs",kernel_kobj);

/*Creating sysfs file for etx_value*/
//if(sysfs_create_file(kobj_ref,&etx_attr.attr)){
  //  printk(KERN_INFO"Cannot create sysfs file......\n");
  //  goto r_sysfs;
//}
//This should be called from exit function
//kobject_put(kobj_ref);

/* static struct file_operations fops =
{
        .owner          = THIS_MODULE,
        .read           = etx_read,
        .write          = etx_write,
        .open           = etx_open,
        .release        = etx_release,
};
 
static ssize_t sysfs_show(struct kobject *kobj, 
                struct kobj_attribute *attr, char *buf)
{
        printk(KERN_INFO "Sysfs - Read!!!\n");
        return sprintf(buf, "%d", etx_value);
}
 
static ssize_t sysfs_store(struct kobject *kobj, 
                struct kobj_attribute *attr,const char *buf, size_t count)
{
        printk(KERN_INFO "Sysfs - Write!!!\n");
        sscanf(buf,"%d",&etx_value);
        return count;
}
 
static int etx_open(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Opened...!!!\n");
        return 0;
}
 
static int etx_release(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "Device File Closed...!!!\n");
        return 0;
}
 
static ssize_t etx_read(struct file *filp, 
                char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Read function\n");
        return 0;
}
static ssize_t etx_write(struct file *filp, 
                const char __user *buf, size_t len, loff_t *off)
{
        printk(KERN_INFO "Write Function\n");
        return 0;
}*/
 
static int __init char_dev_init(void)
//int __init init_module (void)
{

	k_ref = kobject_create_and_add("Sysfs_example", NULL); // Sysfs kernel object
	if ( k_ref  )
	{
		pr_info("kobject_create_and_add function \n");
		return -1;
	}
	
	sysfs_create_file(k_ref, &etx_attr.attr);
	

	return 0;	

}


static void __exit char_dev_exit(void)
//void __exit cleanup_module(void)
{

pr_info(" function \n");
kobject_put(k_ref);
sysfs_remove_file(kernel_kobj, &etx_attr.attr);

}


module_init(char_dev_init);
module_exit(char_dev_exit);

//module_init(sysfs_init);
//module_exit(sysfs_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("naresh");
MODULE_DESCRIPTION(" simple device driver - SysFs");
MODULE_VERSION("1.8");
