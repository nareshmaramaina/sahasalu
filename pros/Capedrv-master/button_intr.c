/*
 * Interrupt generation using Button connected to GPIO.
 * Button connected on GPIO bank 1 pin 13
 * which is located on P8 header pin 11
 * By default the pin is configured as ACTIVE LOW
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

static int gpio, g_irq;

static irqreturn_t button_isr(int g_irq, void *dev_id)
{
	pr_info("%s: IRQ: %d\n", __func__, g_irq);
	return IRQ_HANDLED;
}

static int gpio_button_probe(struct platform_device *pdev)
{
	int ret;

	pr_info("%s: driver inserted\n", __func__);
	gpio = of_get_named_gpio(pdev->dev.of_node, "gpios", 0);
	pr_info("gpio index number: %d\n", gpio);

	
	ret = gpio_request(gpio, NULL);
	if(ret < 0)
		return ret;

	gpio_set_debounce(gpio, 200);

	g_irq = gpio_to_irq(gpio);
	if (g_irq < 0)
		pr_info("couldn't get irq line\n");

	ret = request_threaded_irq(g_irq,   button_isr,  NULL, 
				   IRQF_TRIGGER_RISING, "button_isr_",  NULL);
		if (ret < 0) 
			pr_info("Error: Interrupt Registration Failed\n");

		pr_info("IRQ line: %d\n", g_irq);
	
	return ret;
}

static int gpio_button_remove(struct platform_device *pdev)
{
	pr_info("%s: driver removed\n", __func__);
	free_irq(g_irq, NULL);
	gpio_free(gpio);
	return 0;
}

static struct of_device_id gpio_button_ids[] = {
	{ .compatible = "gpio_button_intr" },
	{ },
};
/* 
 * pass of device id table to kernel using macro MODULE_DEVICE_TABLE, 
 * not doing so will keep kernel unaware of it and the device could not 
 * be matched against the driver
 */
MODULE_DEVICE_TABLE(of, gpio_button_ids);
static struct platform_driver gpio_button_driver =	{
	.probe		= gpio_button_probe,
	.remove		= gpio_button_remove,
	.driver		= {
				.name		= "button_intr",
				.owner 		= THIS_MODULE,
				.of_match_table	= gpio_button_ids,
			},
};

module_platform_driver(gpio_button_driver);

MODULE_DESCRIPTION("GPIO Interrupts");
MODULE_AUTHOR("Team Techveda");
MODULE_LICENSE("GPL");
