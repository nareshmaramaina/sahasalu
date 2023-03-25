#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

#define SUCCESS 0
#define DEVICE_NAME "char_dev"

#define MAJOR_NUM 255

#define WRITE1 0X003
#define READ1 0x002
unsigned char *Buffer="hello world";



static int device_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Device opened");
	printk("device opened in the file %p and with the node %p",file,inode);

	return SUCCESS;
}


static int device_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Device Release");
	printk("device release through the file %p , and inode %p",file,inode);
	return SUCCESS;
}


static ssize_t device_read(struct file *file,char __user * buffer,size_t length,loff_t * offset)
{
int bytes_read=0;

	printk(KERN_INFO "Device read");
/*if (*Buffer == 0)
                return 0;
        while (length && *Buffer) {
                put_user(*(Buffer), buffer++);
                length--;
                bytes_read++;
        }*/
        printk(KERN_INFO "Read %d bytes, %d left\n", bytes_read, length);



/*buffer=Buffer;
for(i=0;i<10;i++)
printk("%c",buffer[i]);
 printk(KERN_INFO "device_read(%p,%p,%d)\n", file, buffer, length);
printk(KERN_INFO "Read %d bytes, %d left\n", bytes_read, length);*/


	return 0;
}

static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset)
{
  printk(KERN_INFO "device_write(%p,%s,%d)", file, buffer, length);
	return 0;
}



int device_ioctl(struct inode *inode,struct file *file,unsigned int ioctl_num,unsigned long ioctl_param)
{
	printk(KERN_INFO "device ioctl %d \n",ioctl_num);

	switch (ioctl_num) 
	{
		case READ1:

			printk("ioctl_read_msg");
			break;
		case WRITE1:
			printk("ioctl_write_msg");

			break;
	}
	return SUCCESS;
}


struct file_operations Fops = {
	.read = device_read,
	.write = device_write,
	.unlocked_ioctl = device_ioctl,
	 .open = device_open,
	.release = device_release,
};

static int hello_init(void)
{
	int ret_val;
	ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);
	if (ret_val < 0) 
	{
		printk(KERN_ALERT "%s failed with %d\n","Sorry, registering the character device ", ret_val);
		return ret_val;
	}
	printk(KERN_INFO "%s The major device number is %d.\n","Registeration is a success", MAJOR_NUM);
	return 0;
}


static void hello_exit(void)
{
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
                                                                                                                                              
 
