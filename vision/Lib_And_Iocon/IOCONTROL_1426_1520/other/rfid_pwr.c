#include <linux/types.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/pm.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/init.h>
#include <linux/gpio.h>

#include <mach/common.h>
#include <mach/hardware.h>
#include <mach/mxc_dvfs.h>
#include <mach/memory.h>
#include <mach/iomux-mx6sl.h>
#include <mach/imx-uart.h>

#include <asm/irq.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/time.h>

#define RFID_PWR_CTRL_PIN      	IMX_GPIO_NR(4,9)

static int __init rfc_usbpwr_init(void)
{


	mxc_iomux_v3_setup_pad(MX6SL_PAD_ECSPI1_MOSI__GPIO_4_9) ; // rfid  power control
	gpio_request(RFID_PWR_CTRL_PIN,"rfid") ;
        gpio_direction_output(RFID_PWR_CTRL_PIN,0);
	gpio_direction_output(RFID_PWR_CTRL_PIN,0) ;
	gpio_set_value(RFID_PWR_CTRL_PIN, 1);
	return 0 ;
}
static void __exit rfc_usbpwr_exit(void)
{
	gpio_set_value(RFID_PWR_CTRL_PIN, 0);
	
}
module_init(rfc_usbpwr_init);
module_exit(rfc_usbpwr_exit)

MODULE_DESCRIPTION("RFC USB  power control driver");
MODULE_AUTHOR("chandanapriya.s@visiontek.co.in");
MODULE_LICENSE("GPL");
