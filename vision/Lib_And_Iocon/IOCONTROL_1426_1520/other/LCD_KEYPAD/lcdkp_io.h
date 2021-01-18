#define BUZZER          0xB8
#define KEY_BUZZER      0xB9
#define TOUCH_BUZZER    0xBA
#define LCD_BKL         0xB1
#define LCD_BKL_TIMEOUT 0xB4
#define BATTER_SENSE    0XA1


#define MX6_BRD_LCD_BACKLIGHT        IMX_GPIO_NR(3, 23)
#define MX6_BRD_KP_BUZZER            IMX_GPIO_NR(3, 7)
#define MX6_BRD_KP_BACKLIGHT         IMX_GPIO_NR(1, 28)
#define MX6_BRD_BAT_SENSE            IMX_GPIO_NR(1, 0)

void setup_init(void){
	gpio_request(MX6_BRD_LCD_BACKLIGHT,"lcdbacklight") ;
        gpio_request(MX6_BRD_KP_BUZZER,"kpbuzzer") ;
        gpio_request(MX6_BRD_KP_BACKLIGHT,"kpbacklight") ;
        gpio_request(MX6_BRD_BAT_SENSE,"batsense") ;


	gpio_direction_output(MX6_BRD_LCD_BACKLIGHT, 0);
        gpio_direction_output(MX6_BRD_KP_BUZZER, 0);
        gpio_direction_output(MX6_BRD_KP_BACKLIGHT, 0);
        gpio_direction_input(MX6_BRD_BAT_SENSE);

}

void setup_exit(void){

	gpio_free(MX6_BRD_LCD_BACKLIGHT);
	gpio_free(MX6_BRD_KP_BUZZER);
	gpio_free(MX6_BRD_KP_BACKLIGHT);


}
