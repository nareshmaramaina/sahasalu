/*
 * =====================================================================================
 *
 *       Filename:  naresh.c
 *
 *    Description:  naresh
 *
 *        Version:  1.0
 *        Created:  Monday 01 March 2021 04:40:35  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */
#include<linux/module.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/init.h>
struct cdev *cdev;
static dev_t dev;
static char gbuff[512];
static int my_open(struct inode *i,  struct file *j)
{
	pr_info(" Open Naresh\n");
	return 0;
}
static int my_close(struct inode *i,  struct file *j)
{
	pr_info(" close naresh\n");
	return 0;
}
static ssize_t my_read(struct file *file, char  *buff,size_t size,loff_t *len)
{
	pr_info(" %d %d \n",strlen(gbuff),*len);
	if ( *len >= strlen(gbuff) )
		return 0;
	pr_info(" My Reading %d %d \n",size,*len);
	copy_to_user(buff,gbuff,512);
	*len = strlen(gbuff);

	pr_info(" Buff = %s gbuff = %s \n", buff,gbuff);
	return *len;
}
static ssize_t my_write(struct file *file,const char  *buff,size_t size,loff_t *len)
{
	pr_info(" My Writeing %d \n",size);
	copy_from_user(gbuff,buff,size);
	pr_info(" Buff = %s gbuff = %s \n", buff,gbuff);
	return size;
}
static struct file_operations fops = {
	.owner=THIS_MODULE,
	.open=my_open,
	.release=my_close,
	.read=my_read,
	.write=my_write,
};


//struct kobject *k_obj;
struct class *k_obj;
//struct kobj_attribute *file=__ATTR(naresh,0777,show,store);

static int __init mastan_init(void)
{
	alloc_chrdev_region(&dev,0,2,"Naresh");
	cdev = cdev_alloc();
	cdev_init(cdev,&fops);
	cdev_add(cdev,dev,1);
	pr_info(" K Google\n");
	k_obj = class_create(THIS_MODULE,"SumoMaya11");
	device_create(k_obj,NULL,dev,NULL,"SumoMastanBhai_11");
	return 0;
}

static void __exit mastan_exit(void)
{
	device_destroy(k_obj,dev);
	class_destroy(k_obj);
	cdev_del(cdev);
	unregister_chrdev(dev,1);
	return;
}
MODULE_LICENSE("GPL");
module_init(mastan_init);
module_exit(mastan_exit);
