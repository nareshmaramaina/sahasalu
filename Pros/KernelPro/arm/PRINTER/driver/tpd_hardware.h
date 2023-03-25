/* Hardware Layer */

#define MX6_BRD_LCD_DAT0_PRN_DATA       IMX_GPIO_NR(2, 0) 
#define MX6_BRD_LCD_DAT1_PRN_CLK        IMX_GPIO_NR(1, 31) 
#define MX6_BRD_LCD_DAT2_PRN_LATCH      IMX_GPIO_NR(2, 2) 
#define MX6_BRD_LCD_DAT3_STROBE1        IMX_GPIO_NR(1, 9) 
#define MX6_BRD_LCD_DAT4_STROBE2        IMX_GPIO_NR(1, 10) 
#define MX6_BRD_LCD_DAT5_STROBE3        IMX_GPIO_NR(1, 11) 
#define MX6_BRD_LCD_DAT6_STROBE4        IMX_GPIO_NR(1, 12) 
#define MX6_BRD_LCD_DAT7_STROBE5        IMX_GPIO_NR(1, 13) 
#define MX6_BRD_LCD_DAT8_STROBE6        IMX_GPIO_NR(1, 14) 
#define MX6_BRD_LCD_DAT9_PRN_IN1        IMX_GPIO_NR(1, 23) 
#define MX6_BRD_LCD_DAT10_PRN_IN2       IMX_GPIO_NR(1, 24) 
#define MX6_BRD_LCD_DAT11_PRN_IN3       IMX_GPIO_NR(1, 7) 
#define MX6_BRD_LCD_DAT12_PRN_IN4       IMX_GPIO_NR(1, 8) 
#define MX6_BRD_LCD_DAT13_VH_CNTRL      IMX_GPIO_NR(3, 8) 
#define MX6_BRD_PAPERSENSE      	IMX_GPIO_NR(2, 1) 
#define MX6_BRD_PRN_SW      		IMX_GPIO_NR(1, 25) 

#define LATCH_LOW       gpio_set_value (MX6_BRD_LCD_DAT2_PRN_LATCH, 0) ;
#define LATCH_HIGH      gpio_set_value (MX6_BRD_LCD_DAT2_PRN_LATCH, 1) ;
#define DATAIN_LOW      gpio_set_value (MX6_BRD_LCD_DAT0_PRN_DATA, 0) ;
#define DATAIN_HIGH     gpio_set_value (MX6_BRD_LCD_DAT0_PRN_DATA, 1) ;
#define CLK_LOW         gpio_set_value (MX6_BRD_LCD_DAT1_PRN_CLK, 0) ;
#define CLK_HIGH        gpio_set_value (MX6_BRD_LCD_DAT1_PRN_CLK, 1) ;
#define STROBE1_LOW     gpio_set_value (MX6_BRD_LCD_DAT3_STROBE1, 0) ;
#define STROBE1_HIGH    gpio_set_value (MX6_BRD_LCD_DAT3_STROBE1, 1) ;
#define STROBE2_LOW     gpio_set_value (MX6_BRD_LCD_DAT4_STROBE2, 0) ;
#define STROBE2_HIGH    gpio_set_value (MX6_BRD_LCD_DAT4_STROBE2, 1) ;
#define STROBE3_LOW     gpio_set_value (MX6_BRD_LCD_DAT5_STROBE3, 0) ;
#define STROBE3_HIGH    gpio_set_value (MX6_BRD_LCD_DAT5_STROBE3, 1) ;
#define STROBE4_LOW     gpio_set_value (MX6_BRD_LCD_DAT6_STROBE4, 0) ;
#define STROBE4_HIGH    gpio_set_value (MX6_BRD_LCD_DAT6_STROBE4, 1) ;
#define STROBE5_LOW     gpio_set_value (MX6_BRD_LCD_DAT7_STROBE5, 0) ;
#define STROBE5_HIGH    gpio_set_value (MX6_BRD_LCD_DAT7_STROBE5, 1) ;
#define STROBE6_LOW     gpio_set_value (MX6_BRD_LCD_DAT8_STROBE6, 0) ;
#define STROBE6_HIGH    gpio_set_value (MX6_BRD_LCD_DAT8_STROBE6, 1) ;
#define IN1_LOW         gpio_set_value (MX6_BRD_LCD_DAT9_PRN_IN1, 0) ;
#define IN1_HIGH        gpio_set_value (MX6_BRD_LCD_DAT9_PRN_IN1, 1) ;
#define IN2_LOW         gpio_set_value (MX6_BRD_LCD_DAT10_PRN_IN2, 0) ;
#define IN2_HIGH        gpio_set_value (MX6_BRD_LCD_DAT10_PRN_IN2, 1) ;
#define IN3_LOW         gpio_set_value (MX6_BRD_LCD_DAT11_PRN_IN3, 0) ;
#define IN3_HIGH        gpio_set_value (MX6_BRD_LCD_DAT11_PRN_IN3, 1) ;
#define IN4_LOW         gpio_set_value (MX6_BRD_LCD_DAT12_PRN_IN4, 0) ;
#define IN4_HIGH        gpio_set_value (MX6_BRD_LCD_DAT12_PRN_IN4, 1) ;
#define VHCNTRL_LOW     gpio_set_value (MX6_BRD_LCD_DAT13_VH_CNTRL, 0) ;
#define VHCNTRL_HIGH    gpio_set_value (MX6_BRD_LCD_DAT13_VH_CNTRL, 1) ;

void setup_port(void)
{

        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_GDOE__GPIO_2_0) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_GDCLK__GPIO_1_31) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_GDSP__GPIO_2_2) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D2__GPIO_1_9) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D3__GPIO_1_10) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D4__GPIO_1_11) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D5__GPIO_1_12) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D6__GPIO_1_13) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D7__GPIO_1_14) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_SDCLK__GPIO_1_23) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_SDLE__GPIO_1_24) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D0__GPIO_1_7) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_D1__GPIO_1_8) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_LCD_DAT20__GPIO_3_8) ;
	
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_GDRL__GPIO_2_1) ;
        mxc_iomux_v3_setup_pad(MX6SL_PAD_EPDC_SDOE__GPIO_1_25) ;
	
        /* MUX PORT */
        gpio_request(MX6_BRD_LCD_DAT0_PRN_DATA,"prn_data");
        gpio_request(MX6_BRD_LCD_DAT1_PRN_CLK,"prn_clk") ;
        gpio_request(MX6_BRD_LCD_DAT2_PRN_LATCH,"prn_latch") ;
        gpio_request(MX6_BRD_LCD_DAT3_STROBE1,"prn_strobe1") ;
        gpio_request(MX6_BRD_LCD_DAT4_STROBE2,"prn_strobe2") ;
        gpio_request(MX6_BRD_LCD_DAT5_STROBE3,"prn_strobe3") ;
        gpio_request(MX6_BRD_LCD_DAT6_STROBE4,"prn_strobe4") ;
        gpio_request(MX6_BRD_LCD_DAT7_STROBE5,"prn_strobe5") ;
        gpio_request(MX6_BRD_LCD_DAT8_STROBE6,"prn_strobe6") ;
        gpio_request(MX6_BRD_LCD_DAT9_PRN_IN1,"prn_prn_in1") ;
        gpio_request(MX6_BRD_LCD_DAT10_PRN_IN2,"prn_prn_in2") ;
        gpio_request(MX6_BRD_LCD_DAT11_PRN_IN3,"prn_prn_in3") ;
        gpio_request(MX6_BRD_LCD_DAT12_PRN_IN4,"prn_prn_in4") ;
        gpio_request(MX6_BRD_LCD_DAT13_VH_CNTRL,"prn_vh_cntrl") ;
        gpio_request(MX6_BRD_PAPERSENSE,"papersense") ;
        gpio_request(MX6_BRD_PRN_SW,"Platenswitch") ;

        gpio_direction_output(MX6_BRD_LCD_DAT0_PRN_DATA, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT1_PRN_CLK, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT2_PRN_LATCH, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT3_STROBE1, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT4_STROBE2, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT5_STROBE3, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT6_STROBE4, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT7_STROBE5, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT8_STROBE6, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT9_PRN_IN1, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT10_PRN_IN2, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT11_PRN_IN3, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT12_PRN_IN4, 0);
        gpio_direction_output(MX6_BRD_LCD_DAT13_VH_CNTRL, 0);
	gpio_direction_input(MX6_BRD_PAPERSENSE);
        gpio_direction_input(MX6_BRD_PRN_SW);
}

void unsetup_port(void)
{
        gpio_free(MX6_BRD_LCD_DAT0_PRN_DATA);
        gpio_free(MX6_BRD_LCD_DAT1_PRN_CLK);
        gpio_free(MX6_BRD_LCD_DAT2_PRN_LATCH);
        gpio_free(MX6_BRD_LCD_DAT3_STROBE1);
        gpio_free(MX6_BRD_LCD_DAT4_STROBE2);
        gpio_free(MX6_BRD_LCD_DAT5_STROBE3);
        gpio_free(MX6_BRD_LCD_DAT6_STROBE4);
        gpio_free(MX6_BRD_LCD_DAT7_STROBE5);
        gpio_free(MX6_BRD_LCD_DAT8_STROBE6);
        gpio_free(MX6_BRD_LCD_DAT9_PRN_IN1);
        gpio_free(MX6_BRD_LCD_DAT10_PRN_IN2);
        gpio_free(MX6_BRD_LCD_DAT11_PRN_IN3);
        gpio_free(MX6_BRD_LCD_DAT12_PRN_IN4);
        gpio_free(MX6_BRD_LCD_DAT13_VH_CNTRL);
}

