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

#define MX6_BRD_KEY_COL5	IMX_GPIO_NR(4,2)

static int __init key_col5_init(void)
{
	
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_COL5__GPIO_4_2) ;
	gpio_request(MX6_BRD_KEY_COL5,"key_col5");
        gpio_direction_output(MX6_BRD_KEY_COL5, 0);
	gpio_set_value(MX6_BRD_KEY_COL5, 1);
	return 0 ;
}
static void __exit key_col5_exit(void)
{
	gpio_set_value(MX6_BRD_KEY_COL5, 0);

}
module_init(key_col5_init);
module_exit(key_col5_exit);

MODULE_DESCRIPTION("USB2517 driver");
MODULE_AUTHOR("malleswari@visiontek.co.in");
MODULE_LICENSE("GPL");
