#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
int hi=0;
dev_t mydev=0;

int init(void);
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
struct cdev *cdevp;

int __init init(void)
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
