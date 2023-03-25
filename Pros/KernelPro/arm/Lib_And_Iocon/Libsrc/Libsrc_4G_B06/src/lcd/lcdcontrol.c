#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include<string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include "spidev.h"


#define LCD_ERR	-1
#define ARG_ERR	-2
#define TRUE     1
#define FALSE    0

#define LCD_BKL_TIMEOUT 0xB4
#define LCD_BKL         0xB1

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static const char *device = "/dev/spidev1.0";
static uint8_t bits = 24;
static uint32_t speed = 500000;
static uint16_t delay;

static int lcd_cfd =-1;

//int lcd_contrast(int chngval)



int gl11_lcd_brightness(int chngval)
{
#if 0
        if(chngval <0 || chngval >127)
        {
                fprintf(stderr,"LIB#LCD Brightness Range 0-127\n");
                return ARG_ERR;
        }
        return ioctl(fd, LCD_BRIT, chngval); 
#endif
        return gl11_lcd_brightness_old(chngval);
}



int gl11_lcd_contrast(int chngval)
{
#if 0
        if(chngval <0 || chngval >31)
        {
                fprintf(stderr,"LIB#LCD Contrast Range 0-31\n");
                return ARG_ERR;
        }
        return ioctl(fd, LCD_CONT, chngval);
#endif
        return gl11_lcd_contrast_old(chngval);
}


int gl11_lcd_default(void)
{
#if 0
        ioctl(fd, LCD_BRIT, 0x40);
        ioctl(fd, LCD_CONT, 0x08);
#endif
        gl11_lcd_contrast_old(0x00);
        gl11_lcd_brightness_old(0x21);
        return 0;
}

int gl11_lcd_contrast_old(int chngval)
{

	lcd_cfd = open(device, O_RDWR | O_NONBLOCK);
	if(lcd_cfd <0)
	{
		fprintf(stderr,"LIB#Can't Open LCD Device\n");
		return LCD_ERR;
	}




	uint8_t tx[] = {
		// 0x01, 0x00, 0x70, 0x00,
		//0x00, 0x21, 0x72, 0x00/*, 0xFF, 0xFF,*/
		0x0a, 0x00, 0x70, 0x00,
		0x08, 0x40, 0x72, 0x00/*, 0xFF, 0xFF,*/
	};

	uint8_t rx[ARRAY_SIZE(tx)] = {0, };
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = ARRAY_SIZE(tx),
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	if(chngval <0 || chngval >31)
	{
		fprintf(stderr,"LIB#LCD Contrast Range 0-31\n");
		return ARG_ERR;
	}

	tx[4] = chngval;
	//printf("tx[4]=%02X\n",chngval);
	if(ioctl(lcd_cfd, SPI_IOC_MESSAGE(1), &tr) ==1)
	{
		fprintf(stderr,"LIB#Can't Set lcd_contrast\n");
		return LCD_ERR;
	}
	return 0;
}

/*0-127*/
int gl11_lcd_brightness_old(int chngval)
{

	lcd_cfd = open(device, O_RDWR | O_NONBLOCK);
	if(lcd_cfd <0)
	{
		fprintf(stderr,"LIB#Can't Open LCD Device\n");
		return LCD_ERR;
	}

	uint8_t tx[] = {
		//	0x01, 0x00, 0x70, 0x00,
		//	0x00, 0x21, 0x72, 0x00/*, 0xFF, 0xFF,*/
		0x0a, 0x00, 0x70, 0x00,
		0x08, 0x40, 0x72, 0x00/*, 0xFF, 0xFF,*/
	};

	uint8_t rx[ARRAY_SIZE(tx)] = {0, };
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = ARRAY_SIZE(tx),
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	if(chngval <0 || chngval >127)
	{
		fprintf(stderr,"LIB#LCD Brightness Range 0-127\n");
		return ARG_ERR;
	}

	tx[5] = chngval;
	//printf("tx[5]=%02X\n",chngval);
	if(ioctl(lcd_cfd, SPI_IOC_MESSAGE(1), &tr)  ==1)
	{
		fprintf(stderr,"LIB#Can't Set lcd_brightness\n");
		return LCD_ERR;
	}
	return 0;
}






