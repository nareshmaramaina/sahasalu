#include <asm/uaccess.h>         // copy_to_user and copy_from_user
#include <linux/init.h>          // modules
#include <linux/module.h>        // module
#include <linux/types.h>         // dev_t type
#include <linux/fs.h>            // chrdev allocation
#include <linux/slab.h>          // kmalloc and kfree
#include <linux/cdev.h>          // struct cdev
#include <linux/errno.h>         // error codes
#include<linux/ioctl.h>
#include<linux/device.h>
#include <linux/kobject.h>

#define NAME "CHANDANA"

typedef struct{
	int rollno;
	char *name;
}variable;


static int rollno=9;
static char *name="chandana";

static int device_open(struct inode *i,struct file *f)
{
	printk("Device opened successfully\n");
	return 0;
}


static int device_release(struct inode *i,struct file *f)
{
	printk("Device released successfully\n");
	return 0;
}


static ssize_t device_write(struct file *f,const char __user *buffer,size_t length,loff_t *offset)
{
	printk("device write\n");
	return 0;
}

static ssize_t device_read(struct file *f,char __user *buffer,size_t length,loff_t *offset)
{
	printk("device read\n");
	return 0;
}

static long device_ioctl(struct file *f,unsigned int cmd,unsigned long param)
{
	variable c;
	switch(cmd)
	{

		case 1:
			printk("get variables\n");
			c.rollno= rollno;
			c.name=name;

			if (copy_to_user((variable *)param, &c, sizeof(variable)))
			{
				return -EACCES;
			}

			printk("roll no=%d",c.rollno);
			printk("name=%s",c.name);
			break;
		case 2:
			printk("set variables\n");
			break;
		case 3:
			printk("clr variables\n");

			break;
	}
	return 0;
}

struct file_operations Fops={
	.open=device_open,
	.read=device_read,
	.write=device_write,
	.release=device_release,
        .unlocked_ioctl=device_ioctl,
	.owner=THIS_MODULE,
};

static int hello_init(void)
{
	register_chrdev(100,NAME,&Fops);
		printk(KERN_INFO"registered successfully \n");
	return 0;
}

static void hello_exit(void)
{
	unregister_chrdev(100,NAME);
	printk(KERN_INFO"unregistered successfully\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CHANDANA");
MODULE_DESCRIPTION("CHAR DRIVER");



