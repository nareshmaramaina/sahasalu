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

//#define MX6_BRD_SD2_DAT5      IMX_GPIO_NR(4, 31)
//#define MX6_BRD_ECSPI2_SS0      IMX_GPIO_NR(4, 15)
//#define MX6_BRD_LCD_DATA19	IMX_GPIO_NR(3, 7)
#define MX6_BRD_LCD_DAT22	IMX_GPIO_NR(3,10)

static int __init fppwr_init(void)
{
	mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT22__GPIO_3_10) ;
	gpio_request(MX6_BRD_LCD_DAT22, "fp_pwr");
        gpio_direction_output(MX6_BRD_LCD_DAT22, 0);
	gpio_set_value(MX6_BRD_LCD_DAT22, 1);
//	mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT19__GPIO_3_7) ;
//	mxc_iomux_v3_setup_pad(MX6SL_PAD_SD2_DAT5__GPIO_4_31) ;
//	gpio_request(MX6_BRD_ECSPI2_SS0, "cs_test");
//	gpio_request(MX6_BRD_LCD_DATA19, "cs1_test");
//	gpio_request(MX6_BRD_SD2_DAT5, "test1");
       // gpio_direction_output(MX6_BRD_ECSPI2_SS0, 0);
        //gpio_direction_output(MX6_BRD_LCD_DATA19, 0);
//        gpio_direction_output(MX6_BRD_SD2_DAT5, 0);
	//gpio_set_value(MX6_BRD_ECSPI2_SS0, 1);
	//gpio_set_value(MX6_BRD_LCD_DATA19, 1);
//	gpio_set_value(MX6_BRD_SD2_DAT5, 1);
	return 0 ;
}
static void __exit fppwr_exit(void)
{
	gpio_set_value(MX6_BRD_LCD_DAT22,0);
//	gpio_set_value(MX6_BRD_ECSPI2_SS0, 0);
//	gpio_set_value(MX6_BRD_LCD_DATA19, 0);
//	gpio_set_value(MX6_BRD_SD2_DAT5, 0);
}
module_init(fppwr_init);
module_exit(fppwr_exit);

MODULE_DESCRIPTION("TEST driver");
MODULE_AUTHOR("malleswari@visiontek.co.in");
MODULE_LICENSE("GPL");
