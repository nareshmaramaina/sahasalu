/* Hardware Layer */

#define GPS_PWR_CNTRL      		    0xA0
#define GSM_PWR_CNTRL   		    0xA1   
#define OPT_CAPPWR_CNTRL  		    0XA2 
#define HOST_PWR_CNTRL		            0XA3 
#define FLASH_CNTRL                        0xA4
#define SELECT_SIM                          0xA5  
#define LCD_BKL_CNTRL	                    0xA6
#define AUD_PWR_CNTRL	                    0xA7
#define BUZZER_CNTRL		            0xA8 
#define IFD_PWR_CNTRL	                    0xA9  
#define CAM_PWR_CNTRL			    0xB0		
#define BLUTH_PWR_CNTRL                     0xB1
#define SAM_PWR_CNTRL                       0xB2
#define GSM_USB_PWR_CNTRL                   0xB3  
#define BATTER_SENSE                        0xB4 
#define LCD_BKL_TIMEOUT                     0xB5    
#define TOUCH_BUZZ_CNTRL                    0xB6   
#define KEY_BUZZ_CNTRL                      0xB7  
#define GSM_M_RESET                         0xB8
#define LCD_BKL_CONT			    0xB9	

#define EXT_USB1                        0xD0
#define EXT_USB2                        0xD1        



#define BRIGHTNESS                          0xc0
#define CONTRAST                            0xc1 

#define BUZZ_TS_KP_TIME			    0xc2				
#define PRN_THERMISTER			    0xc3


#define SERIAL_PWR_CTRL			    0xc4
#define RFU_USB_PWR_CNTRL		    0xc5
#define RFID_PWR_CNTRL			    0xc6
#define WIFI_RF_CNTRL			    0xc7

#define GPIO_PAD_OUT (PAD_CTL_PKE_ENABLE | PAD_CTL_PUE_PUD | PAD_CTL_100K_PU)
#define GPIO_PAD_IN  (PAD_CTL_PKE_ENABLE | PAD_CTL_PUE_PUD | PAD_CTL_100K_PU | PAD_CTL_ODE_OpenDrain) 


#define ioc_set_gpio_value(gpio_pin,val)      gpio_set_value(IOMUX_TO_GPIO(gpio_pin),val)
#define ioc_get_gpio_value(gpio_pin)          gpio_get_value(IOMUX_TO_GPIO(gpio_pin))


/***************************************************/
// i.mx6sl Hardware Layer 

//#define KPD_BKL                 IMX_GPIO_NR(1,28)
#define LCD_BKL                 IMX_GPIO_NR(3,23)
#define AUD_PWR                 IMX_GPIO_NR(1,17)
#define BAT_CHG                 IMX_GPIO_NR(1,0)
#define BUZZ                    IMX_GPIO_NR(3,7)
//#define GPS_ON_OFF_PIN          IMX_GPIO_NR(2,10)

#define GPS_ON_OFF_PIN          IMX_GPIO_NR(4,11)

#define OPT_CAPPWR_EN_PIN       IMX_GPIO_NR(3,10)
#define IFD_PWR_ENABLE_PIN      IMX_GPIO_NR(4,7)
#define BT_PWR_CTRL             IMX_GPIO_NR(3,11)
#define HOST_PWR_CTRL           IMX_GPIO_NR(1,16)
#define SAM_PWR_CTRL            IMX_GPIO_NR(3,31)
#define CAMERA_PWR_CTRL         IMX_GPIO_NR(2,13)
#define GSM_PWR_CTRL            IMX_GPIO_NR(3,9)
#define GSM_USB_PWR_CTRL        IMX_GPIO_NR(3,6)
#define CAMERA_FLASH_CTRL       IMX_GPIO_NR(4,10)
#define RFU_USB_PWR_CTRL_PIN 	IMX_GPIO_NR(4,8)
#define RFID_PWR_CTRL_PIN      	IMX_GPIO_NR(4,9)
#define SIM_SELECT              IMX_GPIO_NR(1,26)
#define GSM_M_RESET_PIN         IMX_GPIO_NR(5,10)
#define BAT_SENSE_PIN           IMX_GPIO_NR(1,0)
#define SERIAL_PWR_PIN  	IMX_GPIO_NR(1,18)
#define WIFI_RF_PWR_CTRL_PIN    IMX_GPIO_NR(3,30)

/*******************************************************/


void imx6sl_hw_init(void)
{
//	mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_SDCE1__GPIO_1_28) ; // KEYPAD_BACKLIGHT
	mxc_iomux_v3_setup_pad(MX6SL_PAD_PWM1__GPIO_3_23) ; // LCD_BACKLIGHT
	mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D10__GPIO_1_17) ; // AUD_PWR_CONTROL
	mxc_iomux_v3_setup_pad(MX6SL_PAD_AUD_RXFS__GPIO_1_0) ; // BAT_SENSE
	mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT19__GPIO_3_7) ; // BUZZER
	mxc_iomux_v3_setup_pad(MX6SL_PAD_ECSPI1_SS0__GPIO_4_11) ;  //GPS_PWR_ONOFF
	mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT22__GPIO_3_10) ; // OPT_CAP_PWR_EN
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_ROW7__GPIO_4_7) ; // IFD Power control
	mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT23__GPIO_3_11) ; // BT PWR control
	mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D9__GPIO_1_16) ; // Host pwr ctrl
	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_ROW3__GPIO_3_31) ; // SAM pwr ctrl
	mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_PWRSTAT__GPIO_2_13) ; // Camera pwr ctrl
	mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT21__GPIO_3_9) ; // Gsm Pwr cntrl
	mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT18__GPIO_3_6) ; // Gsm USB pwr ctrl
	mxc_iomux_v3_setup_pad(MX6SL_PAD_SD1_DAT7__GPIO_5_10) ; // GSM Modem mreset 
	mxc_iomux_v3_setup_pad(MX6SL_PAD_AUD_RXFS__GPIO_1_0) ; // GSM Modem mreset 
	mxc_iomux_v3_setup_pad(MX6SL_PAD_ECSPI1_SCLK__GPIO_4_8) ; //rfu usb power control
	mxc_iomux_v3_setup_pad(MX6SL_PAD_ECSPI1_MOSI__GPIO_4_9) ; // rfid  power control


	mxc_iomux_v3_setup_pad(MX6SL_PAD_KEY_COL3__GPIO_3_30);//wifi power control

//	gpio_request(KPD_BKL, "kpd_bkl");
	gpio_request(LCD_BKL, "lcd_bkl");
	gpio_request(AUD_PWR, "aud_pwr");
	gpio_request(BAT_CHG, "bat_chg");
	gpio_request(BUZZ, "buzzer");
	gpio_request(GPS_ON_OFF_PIN, "gps_pwr_ctrl");
	gpio_request(OPT_CAPPWR_EN_PIN, "opt_cap_pwr_ctrl");
	gpio_request(IFD_PWR_ENABLE_PIN, "ifd_pwr_ctrl");
	gpio_request(BT_PWR_CTRL, "bt_pwr_ctrl");
	gpio_request(HOST_PWR_CTRL, "usb_host_pwr_ctrl");
	gpio_request(SAM_PWR_CTRL, "sam_pwr_ctrl");
	gpio_request(CAMERA_PWR_CTRL, "camera_pwr_ctrl");
	gpio_request(GSM_PWR_CTRL, "gsm_pwr_ctrl");
	gpio_request(GSM_USB_PWR_CTRL, "gsm_usb_pwr_ctrl");
	gpio_request(CAMERA_FLASH_CTRL, "camera_flash_control");
	gpio_request(SIM_SELECT, "sim select");
	gpio_request(GSM_M_RESET_PIN, "gsm pin reset");
	gpio_request(BAT_SENSE_PIN,"batsense") ;
	gpio_request(SERIAL_PWR_PIN,"barcode") ;
	gpio_request(RFU_USB_PWR_CTRL_PIN,"wifi_rf") ;
	gpio_request(WIFI_RF_PWR_CTRL_PIN,"wifi") ;
	gpio_request(RFID_PWR_CTRL_PIN,"rfid") ;


//	gpio_direction_output(KPD_BKL, 0);
	gpio_direction_output(LCD_BKL, 0);
	gpio_direction_output(AUD_PWR, 0);
	gpio_direction_input(BAT_CHG);
	gpio_direction_output(BUZZ, 0);
	gpio_direction_output(GPS_ON_OFF_PIN, 0);
	gpio_direction_output(OPT_CAPPWR_EN_PIN, 0);
	gpio_direction_output(IFD_PWR_ENABLE_PIN, 0);
	gpio_direction_output(BT_PWR_CTRL, 0);
	gpio_direction_output(HOST_PWR_CTRL, 0);
	gpio_direction_output(SAM_PWR_CTRL, 0);
	gpio_direction_output(CAMERA_PWR_CTRL, 0);
	gpio_direction_output(GSM_PWR_CTRL, 0);
	gpio_direction_output(GSM_USB_PWR_CTRL, 0);
	gpio_direction_output(CAMERA_FLASH_CTRL, 1);
	gpio_direction_output(SIM_SELECT, 1);
	gpio_direction_output(GSM_M_RESET_PIN,0);
	gpio_direction_input(BAT_SENSE_PIN);
	gpio_direction_output(SERIAL_PWR_PIN,0);
	gpio_direction_output(RFU_USB_PWR_CTRL_PIN,1) ;
	gpio_direction_output(WIFI_RF_PWR_CTRL_PIN,1) ;
	gpio_direction_output(RFID_PWR_CTRL_PIN,0) ;
}


void imx6sl_hw_deinit(void)
{
//	gpio_free(KPD_BKL);
	gpio_free(LCD_BKL);
	gpio_free(AUD_PWR);
	gpio_free(BAT_CHG);
	gpio_free(BUZZ);
	gpio_free(GPS_ON_OFF_PIN);
	gpio_direction_output(OPT_CAPPWR_EN_PIN, 0);
	gpio_direction_output(IFD_PWR_ENABLE_PIN, 0);
	gpio_direction_output(BT_PWR_CTRL, 0);
	gpio_direction_output(HOST_PWR_CTRL, 0);
	gpio_direction_output(SAM_PWR_CTRL, 0);
	gpio_direction_output(CAMERA_PWR_CTRL, 0);
	gpio_direction_output(GSM_PWR_CTRL, 0);
	gpio_direction_output(GSM_USB_PWR_CTRL, 0);
	gpio_direction_output(CAMERA_FLASH_CTRL, 1);
	gpio_direction_output(SIM_SELECT, 1);
	gpio_free(GSM_M_RESET_PIN);
	gpio_free(BAT_SENSE_PIN);
	gpio_direction_output(SERIAL_PWR_PIN,0);
	gpio_free(RFU_USB_PWR_CTRL_PIN);
	gpio_free(RFID_PWR_CTRL_PIN) ;
	gpio_free(WIFI_RF_PWR_CTRL_PIN) ;
}

