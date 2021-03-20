//#include"/u01/ksrc/KPDS_Kernel/arch/arm/plat-mxc/include/mach/iomux-mx6sl.h"
#include<linux/module.h>
#include<linux/init.h>
short  gpiopin=252;
module_param(gpiopin, short , S_IRUSR ); // Variable, data type , Permissions
MODULE_PARM_DESC(gpiopin, "A short integer"); // Description about variable for modinfo purpose
void my_exit(void)
{
//	gpio_free(gpiopin);

}
//MX6SL_PAD_PWM1__PWM1_PWMO;
int my_init(void)
{
//	mxc_iomux_v3_setup_pad(MX6SL_PAD_PWM1__GPIO_3_23) ; // LCD_BACKLIGHT
	//	mxc_iomux_v3_setup_pad(MX6SL_PAD_PWM1__PWM1_PWMO); // PWM 
	
//	gpio_request(gpiopin, "Naresh");
//	gpio_direction_output(gpiopin, 0); 
	
	int kk[90000];	
	
	memset(kk,0,sizeof(kk));
	return 0;
}
module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Chandana priya.s@visiontek.co.in");
MODULE_DESCRIPTION("GL11 IO CONTROL i.MX6 GPIO port");
MODULE_LICENSE("GPL");
