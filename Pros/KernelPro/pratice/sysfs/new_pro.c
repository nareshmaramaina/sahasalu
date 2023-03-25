#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
 
//#define MYMAJOR	200
#define MYCNT		1
#define MYNAME		"testchar"
 
static dev_t mydev;
static struct cdev test_cdev;
static struct class *test_class;
 
static int test_chrdev_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_open...\n");
	
	return 0;
}
 
static int test_chrdev_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_release...\n");
	
	return 0;
}
 
ssize_t test_chrdev_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos)
{
	printk(KERN_INFO "test_chrdev_read...\n");
	
	return 0;
}
 
static ssize_t test_chrdev_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos)
{
	printk(KERN_INFO "test_chrdev_write...\n");
 
	return 0;
}
 
static const struct file_operations test_fops = {
	.owner		= THIS_MODULE,
	
	.open		= test_chrdev_open,
	.release	= test_chrdev_release,
	.write 		= test_chrdev_write,
	.read		= test_chrdev_read,
};
 
static int __init chrdev_init(void)
{	
	int retval;
	
	printk(KERN_INFO "chrdev_init...\n");
 
	/* Assign primary and secondary device numbers */
/*
	mydev = MKDEV(MYMAJOR, 0);
	retval = register_chrdev_region(mydev, MYCNT, MYNAME);
	if (retval) {
		printk(KERN_ERR "Unable to register minors for %s\n", MYNAME);
		return -EINVAL;
	}
*/
	retval = alloc_chrdev_region(&mydev, 12, MYCNT, MYNAME);
	if (retval < 0) 
	{
		printk(KERN_ERR "Unable to alloc minors for %s\n", MYNAME);
		goto flag1;
	}
	printk(KERN_INFO "alloc_chrdev_region success\n");
	printk(KERN_INFO "major = %d, minor = %d.\n", MAJOR(mydev), MINOR(mydev));
 
	 /* Registered character device driver */
	cdev_init(&test_cdev, &test_fops);
	retval = cdev_add(&test_cdev, mydev, MYCNT);
	if (retval) {
		printk(KERN_ERR "Unable to cdev_add\n");
		goto flag2;
	}
	printk(KERN_INFO "cdev_add success\n");
 
	 /* Create device class */
	test_class = class_create(THIS_MODULE, "test_class");
	if (IS_ERR(test_class)) {
		printk(KERN_ERR "Unable to class_create\n");
		goto flag3;
	}
	
	 /* Create device node */
	device_create(test_class, NULL, mydev, NULL,"test%d" , 0);
 
	return 0;
 
flag3:
	cdev_del(mydev);
 
flag2:
	unregister_chrdev_region(mydev, MYCNT);
flag1:	
	return -EINVAL;
}
 
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit...\n");
 
	 /* Destroy device class node */
	device_destroy(test_class, mydev);
	class_destroy(test_class);
 
	 /* Logout character device driver */
	cdev_del(&test_cdev);
	 /* The primary and secondary device number of the cancellation application */
	unregister_chrdev_region(mydev, MYCNT);
}
 
module_init(chrdev_init);
module_exit(chrdev_exit);
 
 MODULE_LICENSE("GPL"); // Describe the license for the module
 MODULE_AUTHOR("lsm"); // The author of the description module
 MODULE_DESCRIPTION("module test"); // Describe the module's introduction
 MODULE_ALIAS("alias xxx"); // Describe the module's alias information
