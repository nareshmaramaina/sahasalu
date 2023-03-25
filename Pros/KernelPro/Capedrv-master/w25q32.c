/*
 * Winbond W25Qxx SPI Flash Driver
 *
 * Copyright (C) 2016, 2018 Tech Veda <techveda.org>
 * Author:	Team Tech Veda <info@techveda.org>
 *
 * GNU General Public License
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/spi/spi.h>
#include <linux/spi/eeprom.h>
#include <linux/property.h>

#define W25_RDSR	0x05	/* read status register */
#define W25_WREN	0x06	/* set write enable latch */
#define W25_WRITE	0x02	/* write byte(s) */
#define W25_READ	0x03	/* read byte(s) */
#define W25_SEC_ERASE	0x20	/* erase sector */
#define W25_ID		0x9F	/* read manufacturer id*/

#define MN_ID		0xEF	/* manufacturer id */
#define WIP		0x01	/* write-in-progress */
#define TIMEOUT		25	/* timeout in milliseconds */
#define IO_LIMIT	256	/* bytes */

struct w25_priv {
	char			name[10];
        struct spi_device       *spi;
        struct kobject          *kobj;
        long int		offset;
	unsigned		size;
	unsigned		page_size;
	unsigned		addr_width;
	unsigned		block;
	unsigned		sector;
	unsigned		page;
} *prv;

static ssize_t
w25_flash_read(struct w25_priv *w25, char *buf, unsigned offset, size_t count)
{
	struct spi_transfer t[2];
	struct spi_message m;
	ssize_t status;
	u8 cp[5];

	pr_info(" Reading data from block:sector:page <=> 0x%x:0x%x:0x%x \n",
		 w25->block, w25->sector, w25->page);

	memset(buf, '\0', IO_LIMIT);
	memset(t, 0, sizeof(t));

	cp[0] = (u8)W25_READ;
	cp[1] = offset >> 16;
	cp[2] = offset >> 8;
	cp[3] = offset >> 0;

	spi_message_init(&m);

	t[0].tx_buf = cp;
	t[0].len = w25->addr_width/8 + 1;
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = count;
	spi_message_add_tail(&t[1], &m);

	status = spi_sync(w25->spi, &m);
	if (status) {
		pr_err("read %zd bytes at %d --> %d\n",
			count, offset, (int) status);
 		return -EAGAIN;
       }

	return count;
}

static ssize_t
w25_flash_write(struct w25_priv *w25, const char *buf,
		loff_t off, size_t count)
{
	struct spi_transfer t;
	struct spi_message m;
	unsigned long   timeout, retries;
	ssize_t		sr, status = 0;
	u8		*tmp;
	char		cp[2];

	if (count > IO_LIMIT) {
		pr_err("Data IO limit exceeds: Write Operation Terminated\n");
		return -EFBIG;
	}
	
	pr_info(" Writing data to block:sector:page <=> 0x%x:0x%x:0x%x \n",
		 w25->block, w25->sector, w25->page);

	tmp = kmalloc(count + w25->addr_width/8 + 1, GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	cp[0] = (u8)W25_WREN;
	status = spi_write(w25->spi, cp, 1);
	if (status < 0) {
		pr_info("WREN --> %d\n", (int) status);
		return status;
	}
	
	tmp[0] = (u8)W25_WRITE;
        tmp[1] = off >> 16;
        tmp[2] = off >> 8;
        tmp[3] = off >> 0;
	memcpy(tmp + 4, buf, count);

	t.tx_buf = tmp;
	t.len = count + 4;

        spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	
	status = spi_sync(w25->spi, &m);
	if (status) {
		kfree(tmp);
		return -EAGAIN;
	}

	timeout = jiffies + msecs_to_jiffies(TIMEOUT);
	retries = 0;
	/*Check for write in progress status*/
	do {
		sr = spi_w8r8(w25->spi, W25_RDSR);
		if (!(sr & WIP))
			break;

		msleep(1);
	} while (retries++ < 3 || time_before_eq(jiffies, timeout));

	kfree(tmp);

	return count;
}

static ssize_t 
w25_sys_write(struct kobject *kobj, struct kobj_attribute *attr,
	      const char *buf, size_t count)
{
	struct w25_priv *w25 = prv;

	return w25_flash_write(w25, buf, w25->offset, count);
}

static ssize_t
w25_sys_read(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	struct w25_priv *w25 = prv;
	size_t count = IO_LIMIT;

	return w25_flash_read(w25, buf, (int)w25->offset, count);
}

static ssize_t 
w25_set_offset(struct kobject *kobj, struct kobj_attribute *attr,
	       const char *buf, size_t count)
{
	struct w25_priv *w25 = prv;
	unsigned long tmp;
	unsigned int i, j, k;
	char cp[32], temp[32];

	if (!(count == 13 || count == 12))
		return -EFAULT;

	i = j = k = 0;
	for (k = 0; k < 2; k++) {
		memset(cp, '\0', sizeof(cp));
		memset(temp, '\0', sizeof(temp));
		strcpy(temp, buf+j);
		i = 0;
		do {
			if (strncmp(temp+i, ":", 1) != 0) {
				i++; j++;
			} else {
				strncpy(cp, temp, i);
				if (k == 0) {
					if (!kstrtol(cp, 16, &tmp))
						/* Block */
						w25->block = tmp;
				} else if (k == 1) {
					if (!kstrtol(cp, 16, &tmp))
						/* Sector */
						w25->sector = tmp;
				}
				i++; j++;
				break;
			}
		} while (1);
		if (k == 1) {
			strcpy(temp, buf+j);
			if (!kstrtol(temp, 16, &tmp))
				/* Page */
				w25->page = tmp;
		}
	}
	if (w25->block > 0x3f || w25->sector > 0xf || w25->page > 0xf) {
		pr_info("\tOffset must be in following format and range\n");
		pr_info("Blk:sec:page<=><0x00-0x3f>:<0x0-0xf>:<0x0-0xf>\n");
		return -EFAULT;
	}
	w25->offset = (w25->block * 0x10000) + (w25->sector * 0x1000) +
		      (w25->page * 0x100);
	pr_info(" block:sector:page <=> 0x%x:0x%x:0x%x \n",
		 w25->block, w25->sector, w25->page);

	return count;
}

static ssize_t
w25_get_offset(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	struct w25_priv *w25 = prv;

	return sprintf(buf, "block:sector:page\t0x%x:0x%x:0x%x\n",
		       w25->block, w25->sector, w25->page);
}

static ssize_t 
w25_flash_erase(struct kobject *kobj, struct kobj_attribute *attr,
		const char *buf, size_t count)
{
	struct w25_priv *w25 = prv;
	struct spi_transfer t;
	struct spi_message m;
	unsigned long tmp;
	unsigned int block, sector, i, j, k;
	unsigned long timeout, retries;
	ssize_t status, sr;
	char cp[32], temp[32];

	block = sector = 0;
	i = j = k = 0;
	for (k = 0; k < 1; k++) {
		memset(cp, '\0', sizeof(cp));
		memset(temp, '\0', sizeof(temp));
		strcpy(temp, buf + j);
		i = 0;
		do {
			if (strncmp(temp+i, ":", 1) != 0) {
				i++; j++;
			} else {
				strncpy(cp, temp, i);
				if (k == 0) {
					if (!kstrtol(cp, 16, &tmp))
						/* Block */
						block = tmp;
				}
				i++; j++;
				break;
			}
		} while (1);
		if (k == 0) {
			strcpy(temp, buf+j);
			if (!kstrtol(temp, 16, &tmp))
			/* Page */
			sector = tmp;
		}
	}
	if (block > 0x3f || sector > 0xf) {
		pr_info("\tOffset must be in following format and range\n");
		pr_info("Block:sector <=> <0x00-0x3f>:<0x0-0xf>\n");

		return -EAGAIN;
	}

	tmp = (block * 0x10000) + (sector * 0x1000);

	memset(temp, '\0', sizeof(temp));
	temp[0] = W25_WREN;
	status = spi_write(w25->spi, temp, 1);
	if (status < 0)
		pr_info("WREN --> %d\n", (int) status);

	temp[0] = (u8)W25_SEC_ERASE;
	temp[1] = tmp >> 16;
	temp[2] = tmp >> 8;
	temp[3] = tmp >> 0;
	
	t.tx_buf = temp;
        t.len = 4;

        spi_message_init(&m);
        spi_message_add_tail(&t, &m);

        status = spi_sync(w25->spi, &m);
        if (status)
		return -EAGAIN;

        timeout = jiffies + msecs_to_jiffies(TIMEOUT);
        retries = 0;
	/*Check for write in progress status*/
	do {
		sr = spi_w8r8(w25->spi, W25_RDSR);
		if (!(sr & WIP))
			break;

		msleep(1);
	} while (retries++ < 3 || time_before_eq(jiffies, timeout));

	pr_info("block:sector <=> 0x%x:0x%x erased...\n", block, sector);

	return count;
}

static struct kobj_attribute w25_rw =
		__ATTR(w25q32, 0660, w25_sys_read, w25_sys_write);
static struct kobj_attribute w25_offset =
                __ATTR(offset, 0660, w25_get_offset, w25_set_offset);
static struct kobj_attribute w25_erase =
                __ATTR(erase, 0220, NULL, w25_flash_erase);

static struct attribute *attrs[] = {
        &w25_rw.attr,
        &w25_offset.attr,
        &w25_erase.attr,
        NULL,
};

static struct attribute_group attr_group = {
        .attrs = attrs,
};

static int w25_dt_to_chip(struct device *dev)
{
        strcpy(prv->name, "w25q32fv");

        if (device_property_read_u32(dev, "size", &prv->size) < 0)
		pr_err("Error: missing \"size\" property\n");

        if (device_property_read_u32(dev, "pagesize", &prv->page_size) < 0)
		pr_err("Error: missing \"pagesize\" property\n");

	if (device_property_read_u32(dev, "address-width", &prv->addr_width) < 0)
                pr_err("Error: missing \"address-width\" property\n");

        return 0;
}

static int w25_probe(struct spi_device *spi)
{
	ssize_t sr;
	int err;

	prv = devm_kzalloc(&spi->dev, sizeof(struct w25_priv), GFP_KERNEL);
	if (!prv)
		return -ENOMEM;

	w25_dt_to_chip(&spi->dev);
        pr_info("DT Properties Retrieved Successfully\n");

	prv->spi = spi;

	sr = spi_w8r8(prv->spi, W25_ID);
	if (sr == MN_ID)
		pr_info("Device Manufracturer ID Verified\n");
	else {
		pr_info("Manufracturer ID Verifcation Failed\n");
		pr_info("Check Hardware Connections\n");
		return -ENODEV;
	}

	prv->kobj = kobject_create_and_add("w25q32_flash", NULL);
	if(!prv->kobj)
		return -EBUSY;
	
	err = sysfs_create_group(prv->kobj, &attr_group);
	if(err)
		kobject_put(prv->kobj);

	pr_info("\t%s Driver Probed and Registered with sysfs\n", prv->name);
	pr_info("\tW25Q32 Size		:%d\n", prv->size);
	pr_info("\tW25Q32 Page Size	:%d\n", prv->page_size);
	pr_info("\tW25Q32 Address Width	:%d\n", prv->addr_width);

	return 0;
}

static int w25_remove(struct spi_device *spi)
{
	struct w25_priv *w25 = prv;

	pr_info("Driver Removed\n");
	kobject_put(w25->kobj);
	
	return 0;
}

static const struct of_device_id w25_of_match[] = {
	{ .compatible = "winbond,w25q32", },
	{ }
};

static struct spi_driver w25_driver = {
	.driver = {
		.name		= "w25q32",
		.of_match_table = w25_of_match,
	},
	.probe		= w25_probe,
	.remove		= w25_remove,
};

module_spi_driver(w25_driver);

MODULE_DESCRIPTION("Winbond W25Q32/64/128/256 SPI Flash Driver");
MODULE_AUTHOR("Team Techveda <techveda.org>");
MODULE_LICENSE("GPL v2");
