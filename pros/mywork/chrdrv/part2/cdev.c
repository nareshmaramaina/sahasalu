#include<linux/module.h>
//#include<linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define MAJORNO 245 
#define MINORNO  0
#include <linux/device.h>

#define CHAR_DEV_NAME "vDev3"
#define SUCCESS 0

static struct class *veda_class;

struct cdev *cdev;
static dev_t mydev;
static int count = 1;

static int naresh_open(struct inode *inode,struct file *file)
{
	pr_info("Opened Successuly\n");
	return 0;
}
static int naresh_close(struct inode *inode,struct file *file)
{

	pr_info("closed Successuly\n");
	return 0;
}

struct file_operations fops ={
	.owner=THIS_MODULE,
	.open=naresh_open,
	.release=naresh_close,
};

int __init init_module(void )
{
	int ret;

	printk("Naresh:Init entering \n");

/*	mydev=MKDEV(MAJORNO,MINORNO);

	register_chrdev_region(mydev,count,"naresh");

	cdev = cdev_alloc();	

	cdev_init(cdev,&fops);

	ret =	cdev_add(cdev,mydev,count);
	if (ret < 0 )
	{
		pr_info("Failed registration\n");
		return -1;
	}
	return 0;*/


       // mydev = MKDEV(major, minor);

        veda_class = class_create(THIS_MODULE, "VIRTUAL");
        device_create(veda_class, NULL, mydev, NULL, "%s", "vDev3");
	return 0;
}

void __exit cleanup_module(void )
{
	printk("Naresh:Init exiting \n");
	cdev_del(cdev);
	unregister_chrdev_region(mydev,count);
}



//module_init(naresh_init);
//module_exit(naresh_exit);
MODULE_LICENSE("gpl");
MODULE_DESCRIPTION("Naresh driver");
MODULE_AUTHOR("Naresh Yadav");
