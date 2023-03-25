#include <linux/fs.h>
#include<linux/module.h>
#include <linux/device.h>
#include<linux/cdev.h>
#include<linux/ioctl.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include<linux/init.h>
#define DEVICE_NAME "mydev"
#define DEVICE_PATH "/dev/mydev"
static int major_no;
static int device_open(struct inode *inode, struct file *);
static int device_release(struct inode *inode, struct file *);
static long device_ioctl( struct file *, unsigned int, unsigned long);

static int c,a=20,b=30;

static struct class *my_class;

static struct file_operations fops={
	.open = device_open,
	.owner = THIS_MODULE,
	.release = device_release,
	.unlocked_ioctl = device_ioctl,
};
static int __init hello_init(void)
{
	major_no = register_chrdev(0, DEVICE_NAME, &fops);
	printk("\n Major_no : %d", major_no);

	my_class = class_create(THIS_MODULE, DEVICE_NAME);
	device_create(my_class, NULL, MKDEV(major_no,0), NULL, DEVICE_NAME);
	printk("\n Device Initialized in kernel ....!!!");
	return 0;
}


static void __exit hello_exit(void)
{
	printk("\n Device is Released or closed \n");
	device_destroy(my_class,MKDEV(major_no,0));
	class_unregister(my_class);
	class_destroy(my_class);
	unregister_chrdev(major_no, DEVICE_NAME);
	printk("\n================================\n");
}

static int device_open(struct inode *inode, struct file *file)
{
	printk("\n Open \n");
	return 0;
}

static long device_ioctl(struct file *file, unsigned int cmd, unsigned long args)
{


	printk(KERN_INFO "am in device ioctl\n");
	switch(cmd)
	{
		case 1:
			printk(KERN_INFO"\n Write \n");
			printk(KERN_INFO "THIS IS CREDIBLE:\n");
			c=a+b;
			printk(KERN_INFO"C value is %d\n",c);		
			break;

		case 2:
			printk(KERN_INFO"READ\n");
			break;

	}
	return 0;
}


static int device_release(struct inode *inode, struct file *file)
{
	printk("\n Release \n");
	return 0;
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
