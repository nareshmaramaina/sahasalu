/*
 * AM3358 GPIO LED Driver
 *
 * Copyright (C) 2016, 2018 Tech Veda <techveda.org>
 * Author:	Team Tech Veda <info@techveda.org>
 *
 * GNU General Public License
 */

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/of_gpio.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <asm/io.h>

#define OMAP_GPIO_OE			0x0134
#define OMAP_GPIO_DATAOUT		0x013C
#define OMAP_GPIO_CLEARDATAOUT		0x0190
#define OMAP_GPIO_SETDATAOUT		0x0194

struct gpiopin_bank {
        u32 gpio_base;
	unsigned int pinno;
} *gpbank;

static void	*gbank_base;
static struct	kobject *kobj;
static bool	flag = true;

void pin_config(void)
{
	u32 data = 0;	

	if (flag) {
		data = readl_relaxed(gbank_base + OMAP_GPIO_OE);
		data = data & ~(1U << gpbank->pinno);
		writel_relaxed(data, gbank_base + OMAP_GPIO_OE);

		pr_info("GPIO Pin Initialized\n");
	}
	else {
		data = 1U << gpbank->pinno;
		writel_relaxed(data, gbank_base + OMAP_GPIO_CLEARDATAOUT);

		data = readl_relaxed(gbank_base + OMAP_GPIO_OE);
		data = data | (1U << gpbank->pinno);
		writel_relaxed(data, gbank_base + OMAP_GPIO_OE);

		pr_info("GPIO Pin Configuration Restored\n");
	}

	flag = false;
}

static ssize_t extled_read(struct kobject *kobj,
			   struct kobj_attribute *attr,
			   char *buf) 
{
	u32 data = 0;

        data = readl_relaxed(gbank_base + OMAP_GPIO_DATAOUT);
	data = data & (1U << gpbank->pinno) ? 1 : 0;

	if (data)
		return sprintf(buf, "%s\n", "LED ON");
	else
		return sprintf(buf, "%s\n", "LED OFF");
}

static ssize_t extled_write(struct kobject *kobj,
			    struct kobj_attribute *attr,
			    const char *buf,
			    size_t count)
{
	int input, ret;
	u32 data = 0;	

	ret = sscanf(buf, "%d", &input);
	if(ret < 0 || ret > 1 || input > 1)
               return -EINVAL;

	if(input) {
		data = 1U << gpbank->pinno;
		writel_relaxed(data, gbank_base + OMAP_GPIO_SETDATAOUT);
	}
        else {
		data = 1U << gpbank->pinno;
		writel_relaxed(data, gbank_base + OMAP_GPIO_CLEARDATAOUT);
	}

	return count;
}

static struct kobj_attribute led_attr =
	__ATTR(extled, 0660, extled_read, extled_write);

static int led_probe(struct platform_device *pdev)
{
	struct device_node *pnode;
	int ret;

	pr_info("Driver Registered with Platform Core\n");
	gpbank = (struct gpiopin_bank *)kmalloc(sizeof(struct gpiopin_bank),
						GFP_KERNEL);

	gpbank->pinno = of_get_named_gpio(pdev->dev.of_node, "gpios", 0);

	pnode = of_parse_phandle(pdev->dev.of_node, "gpios", 0);	

	ret = of_property_read_u32(pnode, "reg", &gpbank->gpio_base);

	gbank_base = ioremap(gpbank->gpio_base, 4095);
	if (!gbank_base) 
		return -1;

	kobj = kobject_create_and_add("ext_led", NULL);
	if(!kobj)
		return -ENOMEM;

	ret = sysfs_create_file(kobj, &led_attr.attr);
	if(ret)
		kobject_put(kobj);

	pin_config();

	pr_info("PROBE: GPIO PIN: %u\n", gpbank->pinno);
	pr_info("PROBE: GPIO Bank Physical Address: %x\n", gpbank->gpio_base);
	pr_info("PROBE: GPIO Bank Virtual Address: %p\n", gbank_base);

	return 0;
}

static int led_remove(struct platform_device *pdev)
{
	pr_info("Driver Unregistered from Platform Core\n");

	pin_config();
	iounmap(gbank_base);
	kobject_put(kobj);
	kfree(gpbank);

        return 0;
}

static const struct of_device_id led_of_mtable[] = {
        { .compatible = "gpio_extled", },
		{}
};
MODULE_DEVICE_TABLE(of, led_of_mtable);
 
static struct platform_driver led_driver = {
         .driver = {
                 .name    = "off-board_led",
		 .owner   = THIS_MODULE,		
                 .of_match_table = led_of_mtable,
         },
         .probe = led_probe,
         .remove = led_remove,
};
module_platform_driver(led_driver); 

MODULE_AUTHOR("Team TechVeda <info@techveda.org>");
MODULE_DESCRIPTION("AM3358 GPIO LED Driver");
MODULE_LICENSE("GPL");
