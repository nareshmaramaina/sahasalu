#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/fs.h>		/* for register_chardev, file_operations  etc. */
#include <linux/init.h> 
#include <linux/mm.h>
#include <linux/sched.h>	/* for jiffies */
#include <asm/uaccess.h>	/*  for copy_from_user    */
#include <asm/io.h>		/* to access io memory */
#include <mach/hardware.h>
#include <mach/gpio.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/imx_adc.h>
#include <linux/kernel.h>
#include <linux/kthread.h>

#include <linux/interrupt.h>
#include <mach/hardware.h>
#include <mach/gpio.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/clk.h>
#include"/u01/ksrc/KPDS_Kernel/arch/arm/plat-mxc/include/mach/iomux-mx6sl.h"
short  gpiopin=252;
module_param(gpiopin, short , S_IRUSR ); // Variable, data type , Permissions
MODULE_PARM_DESC(gpiopin, "A short integer"); // Description about variable for modinfo purpose
void my_exit()
{
	gpio_free(gpiopin);

}
//MX6SL_PAD_PWM1__PWM1_PWMO;
int my_init()
{
	mxc_iomux_v3_setup_pad(MX6SL_PAD_PWM1__GPIO_3_23) ; // LCD_BACKLIGHT
	//	mxc_iomux_v3_setup_pad(MX6SL_PAD_PWM1__PWM1_PWMO); // PWM 

	gpio_request(gpiopin, "Naresh");
	gpio_direction_output(gpiopin, 0); 

	return 0;
}
module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Chandana priya.s@visiontek.co.in");
MODULE_DESCRIPTION("GL11 IO CONTROL i.MX6 GPIO port");
MODULE_LICENSE("GPL");
