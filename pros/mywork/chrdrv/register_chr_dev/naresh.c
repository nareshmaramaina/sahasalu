#include <linux/module.h>
//#include <linux/version.h>
//#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define MAJORNO 0		
#define MINORNO 0
#define CHAR_DEV_NAME "Char_dev"
static struct cdev *cdev;
static dev_t  my_dev;
static int count=3;
static int naresh_open(struct inode *inode, struct file *file )
{
	
	pr_info(" %s success \n",__func__);
	return 0;
}
static int naresh_close(struct inode *inode, struct file *file )
{
	pr_info(" %s success \n",__func__);
	return 0;
}

static struct file_operations file_ops = {

	.owner = THIS_MODULE,
	.open = naresh_open,
	.release = naresh_close

};

///int   __init init_module(void)
int  __init init_module(void)
{
	int ret;
	pr_info("Hai Ra Mama first p\n");

	
//	my_dev = MKDEV(MAJORNO,MINORNO);

	my_dev = register_chrdev_region(my_dev,count,CHAR_DEV_NAME);

	cdev = cdev_alloc();

	cdev_init(cdev,&file_ops);

	ret = cdev_add(cdev,my_dev,count);	
	if ( ret < 0 )
	{
		pr_info("Registration file success\n");
		return -1;
	}
	pr_info(" %s Succesfuly reg Major Number = %d\n",CHAR_DEV_NAME,my_dev);
	


	return 0;
}

void  __exit cleanup_module(void)
{
	cdev_del(cdev);
	unregister_chrdev_region(my_dev,count);
	pr_info("Bye Ra Mama  p\n");
	return;
}
MODULE_AUTHOR("www.techveda.org");
MODULE_DESCRIPTION("LKD_CW: Character Device Driver - Test");
MODULE_LICENSE("GPL");

//module_init(init_module1);
//module_exit(cleanup_module1);
