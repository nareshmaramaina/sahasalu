#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/kobject.h> 
#include<linux/sysfs.h> 
int hi=0;
dev_t mydev=0;
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

int  myopen(struct inode *inode,struct file *file)
{
	pr_info("File Opened\n");
	return 0;
}
int myclose(struct inode *inode,struct file *file)
{
	pr_info("File closed\n");
	return 0;
}
struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = myopen,
	.release = myclose
};


static ssize_t myshow(struct kobject *kobj,struct kobj_attribute *kattr,char *buf)
{
	pr_info("file=  %s\n",buf);
	return 0;
}
static ssize_t mystore(struct kobject *kobj,struct kobj_attribute *kattr,const char *buf,size_t  count)
{
	pr_info("Count = %d , Buffer = %s\n",count,buf);
	return count;
}
struct cdev *cdevp;
struct kobject *kobj;
struct kobj_attribute kobj_attr=__ATTR(value,0660,myshow,mystore);
int  init(void)
{
	int ret;
	pr_info("Module Init\n");

	ret = alloc_chrdev_region(&mydev,2,2,"maresh"); // &dev Num , Minor 2 , 2,  2,3 
	if (ret < 0 )
	{	
		pr_info("Registration failed\n");
		return -1;	
	}
	cdevp = cdev_alloc(); // Allocate cdev instance 
	cdev_init(cdevp,&fops); // Initilize cdev instance with fops 
	cdev_add(cdevp,mydev,2); // Register device with vfs 
	
	kobj = kobject_create_and_add("Naresh",NULL);
	if ( kobj == NULL )
	{
		pr_info("kobj failed \n");
		return -1;
	}
	
	sysfs_create_file(kobj,&kobj_attr.attr);

	return 0;
}
void myexit(void)
{
	unregister_chrdev_region(mydev,2);
	cdev_del(cdevp);
	pr_info("Module Exit\n");
	return;
}
module_init(init);
module_exit(myexit);
MODULE_LICENSE("GPL");
