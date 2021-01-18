#include <linux/init.h>
#include<linux/sched.h>//for current comm and pid
#include<linux/fs.h>//for allocating and freeing device numbers
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/gpio.h>


#include "../arch/arm/mach-mx6/board-mx6sl_common.h"
#include "../arch/arm/plat-mxc/include/mach/iomux-mx6sl.h"
#include<linux/gpio.h>


MODULE_LICENSE("Dual BSD/GPL");

#define GSM_M_RESET   IMX_GPIO_NR(5, 10)

static int gl865_reset_init(void)
{
	mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_DAT7__GPIO_5_10) ; // GSM Modem mreset 
	gpio_request(GSM_M_RESET,"gl865 reset");
	gpio_direction_output(GSM_M_RESET,0);
	gpio_set_value(GSM_M_RESET,0);
	gpio_set_value(GSM_M_RESET,1);
	mdelay(250);
	gpio_set_value(GSM_M_RESET,0);
	mdelay(1000);

	return 0;
}

static void gl865_reset_exit(void)
{

	gpio_set_value(GSM_M_RESET,0);	
	gpio_free(GSM_M_RESET);
}

module_init(gl865_reset_init);
module_exit(gl865_reset_exit);

