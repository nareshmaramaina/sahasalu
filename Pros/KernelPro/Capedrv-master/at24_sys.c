/*
 * Author : techveda.org
 * This driver handles read/write operations on 24C32N eeprom(4096 bytes)
 * 24C32N should be connected on pin 19 (SCL) and pin 20(SDA) of beagle bone
 * black P9 header. Driver uses sysfs for user interaction.
 * GNU General Public License
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include "at24_sys.h"

struct at24_prv *prv = NULL;

static unsigned read_limit = 32;
static unsigned write_max = 32;
static unsigned write_timeout = 25;

static ssize_t at24_eeprom_read(struct i2c_client *client, char *buf,
		unsigned offset, size_t count)
{
	struct i2c_msg msg[2];
	u8 msgbuf[2];
	unsigned long timeout, read_time;
	int status;
	memset(msg, 0, sizeof(msg));
	memset(msgbuf, '\0', sizeof(msgbuf));
	if (count > read_limit)
		count = read_limit;

	msgbuf[0] = offset >> 8;
	msgbuf[1] = offset;

	msg[0].addr = client->addr;

	msg[0].flags = 0;
	msg[0].buf = msgbuf;

	msg[0].len = 2;
	
	msg[1].addr = client->addr;
	msg[1].flags = 1;
	msg[1].buf = buf;
	msg[1].len = count;

	timeout = jiffies + msecs_to_jiffies(write_timeout);
	do {
		read_time = jiffies;

		status = i2c_transfer(client->adapter, msg, 2);
		if (status == 2)
			status = count;
		if (status == count) {
			return count;
		}
		msleep(1);
	} while (time_before(read_time, timeout));

	return -ETIMEDOUT;
}

static ssize_t at24_eeprom_write(struct i2c_client *client, const char *buf,
				 unsigned offset, size_t count)
{
	struct i2c_msg msg;
	unsigned long timeout, write_time;
	ssize_t status;
	char msgbuf[40];

	memset(msgbuf, '\0', sizeof(msgbuf));
	if (count >= write_max)
		count = write_max;

	msg.addr = client->addr;

	msg.flags = 0;
	msg.buf = msgbuf;

	msg.buf[0] = (offset >> 8);
	msg.buf[1] = offset;

	memcpy(&msg.buf[2], buf, count);

	msg.len = count + 2;
	timeout = jiffies + msecs_to_jiffies(write_timeout);
	do {
		write_time = jiffies;
		status = i2c_transfer(client->adapter, &msg, 1);
		if (status == 1)
			status = count;
		if (status == count)
			return count;
		msleep(1);
	} while (time_before(write_time, timeout));

	return -ETIMEDOUT;
}

static ssize_t
at24_sys_write(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	ssize_t ret;

	loff_t off = prv->page_no * 32;

	if (count > write_max) {
		pr_info("write length must be <= 32\n");
		return -EFBIG;
	}
	ret = at24_eeprom_write(&prv->client_prv, buf, (int)off, count);
	if (ret < 0) {
		pr_info("write failed\n");
		return ret;
	}

	return count;
}

static ssize_t
at24_sys_read(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	ssize_t ret;
	
	loff_t off = prv->page_no * 32;
	
	ret = at24_eeprom_read(&prv->client_prv, buf, (int)off, prv->pagesize);
	if (ret < 0) {
		pr_info("error in reading\n");
		return ret;
	}
	
	return prv->pagesize;
}

static ssize_t
at24_get_offset(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	pr_info("Page: %d\n", prv->page_no);

	return strlen(buf);
}

static ssize_t
at24_set_offset(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	unsigned int long tmp;

	if (!kstrtol(buf, 16, &tmp)) {
		if (tmp < 128) {
			prv->page_no = tmp;
			pr_info("Page: %d\n", prv->page_no);
		} else {
			pr_info("128 pages are available\n");
			pr_info("Choose pages from 0x0 - 0x80\n");
		}
	}

	return count;
}

static struct kobj_attribute at24_rw = __ATTR(at24c32, 0660, at24_sys_read,
						at24_sys_write);
static struct kobj_attribute at24_offset = __ATTR(offset, 0660,
						at24_get_offset, at24_set_offset);

static struct attribute *attrs[] = {
        &at24_rw.attr,
        &at24_offset.attr,
        NULL,
};

static struct attribute_group attr_group = {
        .attrs = attrs,
};

static int at24_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret;

	pr_info("Device at24c32 probed......\n");

	prv = (struct at24_prv *)kzalloc(sizeof(struct at24_prv), GFP_KERNEL);
	if (prv == NULL) {
		pr_info("Requested memory not allocated\n");
		return -ENOMEM;
	}
	prv->client_prv = *client;
		
	if (device_property_read_u32(&client->dev, "size", &prv->size) == 0) {
	} else {
		dev_err(&client->dev, "Error: missing \"size\" property\n");
		return -ENODEV;
	}
	if (device_property_read_u32(&client->dev, "pagesize", &prv->pagesize) == 0) {
	} else {
		dev_err(&client->dev, "Error: missing \"pagesize\" property\n");
		return -ENODEV;
	}
	if (device_property_read_u32(&client->dev, "address-width", &prv->address_width)) {
		dev_err(&client->dev, "Error: missing \"address-width\" property\n");
		return -ENODEV;
	}

	prv->at24_kobj = kobject_create_and_add("at24c32_eeprom", NULL);
	if(!prv->at24_kobj)
		return -ENOMEM;
	
	ret = sysfs_create_group(prv->at24_kobj, &attr_group);
	if(ret)
		kobject_put(prv->at24_kobj);

	pr_info("Sysfs entry created for AT24C32 device \n");
	pr_info("	SIZE		:%d\n", prv->size);
	pr_info("	PAGESIZE	:%d\n", prv->pagesize);
	pr_info("	address-width	:%d\n", prv->address_width);

	return 0;
}

static int at24_remove(struct i2c_client *client)
{
	pr_info("at24_remove\n");
	
	kfree(prv);
	kobject_put(prv->at24_kobj);
	
	return 0;
}

static const struct i2c_device_id at24_ids[] = {
	{ "24c32", 0x50 },
	{ /* END OF LIST */ }
};

static struct i2c_driver at24_driver = {
	.driver = {
		.name = "at24",
		.owner = THIS_MODULE,
	},
	.probe = at24_probe,
	.remove = at24_remove,
	.id_table = at24_ids,
};

module_i2c_driver(at24_driver);

MODULE_DESCRIPTION("Driver for at24c32 eeprom");
MODULE_AUTHOR("techveda.org");
MODULE_LICENSE("GPL");
