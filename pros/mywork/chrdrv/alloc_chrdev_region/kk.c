#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include <linux/uaccess.h>
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

ssize_t myread(struct file *file, char  *buff, size_t size,loff_t *k)
{
//	copy_to_user(buff,"Hlo",3);	
	pr_info("Read %d\n",*k);
		strcpy(buff,"Hlo");
	if ( *k > 100)
		return EINVAL;
	*k=*k+3;
	return 3;
}
ssize_t mywrite(struct file *file, const  char  *buff, size_t size,loff_t *k)
{
	pr_info("Write %10s \n",buff);     
	return size;
}

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = myopen,
	.read = myread,
	.write = mywrite,
	.release = myclose
};
struct cdev *cdevp;

int __init init(void)
{
	int ret;
	pr_info("Module Init\n");

	ret = alloc_chrdev_region(&mydev,2,2,"maresh"); // &dev Num , Minor 2 , 2,  2,3 
	pr_info("REgisterted Numer %d\n",ret);
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
	cdev_del(cdevp);
	unregister_chrdev_region(mydev,2);
	pr_info("Module Exit\n");
	return;
}
module_init(init);
module_exit(myexit);
MODULE_LICENSE("GPL");
