/*
 * keyboard.c
 *
 * Example of kernel module that implements a keyboard interrupt
 * handler.  The module creates the entry /dev/kbd that applications
 * can use to catch keyboard events. By reading from that device, a
 * process will block until a key is pressed or released. For
 * simplicity, the device does not support writing and more complex
 * configuration.
 *
 * REQUIREMENTS
 * 
 * This module binds to the keyboard interrupt and shares it with the
 * native Linux keyboard interrupt handler. The native handler needs
 * to be modified to support interrupt sharing. See
 * src/include/asm-i386/keyboard.h for more information.
 *
 * Device File System (devfs), Linux Kernel 2.4.x
 *
 * AUTHOR
 *
 * Emanuele Altieri
 * ealtieri@hampshire.edu
 * June 2002
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/fs.h>
//#include <linux/devfs_fs_kernel.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define KBD_IRQLINE 1 

static void kbd_irq_handler(int, void*, struct pt_regs*);
static ssize_t kbd_read(struct file*, char*, size_t, loff_t*);

/* file operations */

static struct file_operations kbd_fops = {
	read:    kbd_read,
};

/* data */

static devfs_handle_t kbd_handle;
static char* kbd_device = "kbd";
static unsigned short kbd_buffer = 0x0000; /* HByte=Status, LByte=Scancode */
static wait_queue_head_t kbd_irq_waitq;

int __init kbd_init(void)
{
	/* register device */
	SET_MODULE_OWNER(&kbd_fops);
	kbd_handle = devfs_register(NULL, kbd_device, 
				    DEVFS_FL_AUTO_DEVNUM | DEVFS_FL_AUTO_OWNER,
				    0, 0, S_IFCHR | S_IRUSR, 
				    &kbd_fops, NULL); 
	if (kbd_handle <= 0) {
		printk(KERN_ERR "%s: cannot register device\n", kbd_device);
		goto fail_devfs;
	}
	/* request interrupt line */
	if (request_irq(KBD_IRQLINE, kbd_irq_handler, SA_SHIRQ, 
			kbd_device, (void*) &kbd_handle) < 0) {
		printk(KERN_CRIT "%s: interrupt line busy\n",kbd_device);
		goto fail_irq;
	}
	/* initialize waiting queue */
	init_waitqueue_head(&kbd_irq_waitq);
	return(0);

 fail_irq:
	devfs_unregister(kbd_handle);
 fail_devfs:
	return(-EBUSY);
} // kbd_init()

void __exit kbd_cleanup(void)
{
	devfs_unregister(kbd_handle);
	free_irq(KBD_IRQLINE, (void*) &kbd_handle);
} // kbd_cleanup()

// Put current process to sleep. The process will be awaken by the
// interrupt handler when an keyboard interrupt occurs. The character
// code and keyboard status is then sent to the process.
static ssize_t 
kbd_read(struct file *filp, char *buf, size_t count, loff_t* f_pos)
{
	interruptible_sleep_on(&kbd_irq_waitq);
	copy_to_user((void*) buf, (void*) &kbd_buffer, sizeof(kbd_buffer));
	return(sizeof(kbd_buffer));
} // kbd_read()

// Keyboard interrupt handler. Retrieves the character code (scancode)
// and keyboard status from the keyboard I/O ports. Awakes processes
// waiting for a keyboard event.
static void kbd_irq_handler(int irq, void* dev_id, struct pt_regs *regs)
{
	unsigned char status, scancode;
	status = inb(0x64);
	scancode = inb(0x60);
	kbd_buffer = (unsigned short) ((status << 8) | (scancode & 0x00ff));
	wake_up_interruptible(&kbd_irq_waitq);
} // kbd_irq_handler()

MODULE_AUTHOR("Emanuele Altieri (ealtieri@hampshire.edu)");
MODULE_DESCRIPTION("Simple keyboard device driver");
MODULE_LICENSE("GPL");

module_init(kbd_init);
module_exit(kbd_cleanup);
