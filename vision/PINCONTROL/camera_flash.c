/* GPIO control driver for i.MX6SL EVK Board */
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

#define MX6_BRD_ECSPI1_MISO	IMX_GPIO_NR(4,10)

static int __init camera_flash_init(void)
{
	mxc_iomux_v3_setup_pad(MX6SL_PAD_ECSPI1_MISO__GPIO_4_10) ;
	gpio_request(MX6_BRD_ECSPI1_MISO, "camera_flash_ctrl");
        gpio_direction_output(MX6_BRD_ECSPI1_MISO, 0);
	gpio_set_value(MX6_BRD_ECSPI1_MISO, 0);
	return 0 ;
}
static void __exit camera_flash_exit(void)
{
	gpio_set_value(MX6_BRD_ECSPI1_MISO, 1);
}
module_init(camera_flash_init);
module_exit(camera_flash_exit);

MODULE_DESCRIPTION("camera flash cntrl driver");
MODULE_AUTHOR("malleswari@visiontek.co.in");
MODULE_LICENSE("GPL");
