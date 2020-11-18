#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <termios.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>


#define GPS_PWR_CNTRL                       0xA0
#define GSM_PWR_CNTRL                       0xA1   
#define OPT_CAPPWR_CNTRL                    0XA2 
#define HOST_PWR_CNTRL                      0XA3 
#define FLASH_CNTRL                         0xA4
#define SELECT_SIM                          0xA5  
#define LCD_BKL_CNTRL                       0xA6
#define AUD_PWR_CNTRL                       0xA7
#define BUZZER_CNTRL                        0xA8 
#define IFD_PWR_CNTRL                       0xA9  
#define CAM_PWR_CNTRL                       0xB0                
#define BLUTH_PWR_CNTRL                     0xB1
#define SAM_PWR_CNTRL                       0xB2
#define GSM_USB_PWR_CNTRL                   0xB3  
#define BATTER_SENSE   			    0xB4
#define LCD_BKL_TIMEOUT 		    0xB5
#define TOUCH_BUZZ_CNTRL                    0xB6
#define KEY_BUZZ_CNTRL                      0xB7
#define ARG_ERR -2
#define TRUE 1
#define FALSE 0



struct get_batsense
{
        int batsense_val;
}__attribute__ ((packed));
struct get_batsense get_batterysense;

extern int get_node_readvalue(const char *node_name);

typedef unsigned char UC;
static int fd;



int gl11_iodev_open()
{
	int ret;
	fd=open("/dev/ioc",O_RDWR|O_NONBLOCK);
	if( fd == -1)
	{
		fprintf(stderr,"IODEVICE open failed\n");
		return -1;
	}
	return 0;
}

int gl11_iodev_close()
{
	int ret;
	
	ret=close(fd);
	
	return ret;
}	


int gl11_gpsctrl(int val)
{

int ret=0;

return 0;

}

int gl11_wifi_control(int val)
{

int ret=0;

return ret;

}




int gl11_gps_pwron(void)
{
	int ret=0;
	
	ret=ioctl(fd,GPS_PWR_CNTRL,TRUE);
	
	return ret;
}
int gl11_gps_pwroff(void)
{
	int ret=0;
	
	ret=ioctl(fd,GPS_PWR_CNTRL,FALSE);
		
	return ret;
}
int gl11_gsmpwrctrl(int val)
{
	int ret=0;
	
	if(val==0 || val==1)
	{
		if(val)
		{
			ret=ioctl(fd,GSM_PWR_CNTRL,TRUE);
			return ret;
		}
		else
		{
			ret=ioctl(fd,GSM_PWR_CNTRL,FALSE);
			return ret;	
		}
	}
	else
	{

		fprintf(stdout,"Enter Valid Input as 0 or 1\n");
		return ARG_ERR;
	}
}
int gl11_optcap_pwron(void)
{
	int ret=0;
	
	ret=ioctl(fd,OPT_CAPPWR_CNTRL,TRUE);
		
	return ret;
}
int gl11_optcap_pwroff(void)
{
	int ret=0;
	
	ret=ioctl(fd,OPT_CAPPWR_CNTRL,FALSE);
	
	return ret;
}
int gl11_host_pwron(void)
{
        int ret;
        ret=ioctl(fd,HOST_PWR_CNTRL,TRUE);

        return ret;
}

int gl11_host_pwroff(void)
{
        int ret;
        ret=ioctl(fd,HOST_PWR_CNTRL,FALSE);

        return ret;
}

int gl11_internal_camflash(int val)
{

	int ret=0;

	if(val==0||val==1)
	{
		if(val)
		{
			ret=ioctl(fd,FLASH_CNTRL,TRUE);
			return ret;
		}
		else
		{
			ret=ioctl(fd,FLASH_CNTRL,FALSE);
			return ret;	
		}

	}
	else
	{
		fprintf(stdout,"Enter Valid Input as 0 or 1\n");
		return ARG_ERR;
	}
}

int gl11_simselect(int val)
{
	int ret=0;

	if(val==0||val==1)
	{
		if(val)
		{
			ret=ioctl(fd,SELECT_SIM,TRUE);
			return ret;
		}
		else
		{
			ret=ioctl(fd,SELECT_SIM,FALSE);
			return ret;	
		}
	}
	else
	{
		fprintf(stdout,"Enter Valid Input as 0 or 1\n");
		return ARG_ERR;
	}
}

int gl11_lcdbklt_on(void)
{
	int ret=0;

	ret=ioctl(fd,LCD_BKL_CNTRL,TRUE);

	return ret;
}
int gl11_lcdbklt_off(void)
{
	int ret=0;

	ret=ioctl(fd,LCD_BKL_CNTRL,FALSE);

	return ret;
}


int gl11_audio_power_on(void)
{
	int ret;
	ret=ioctl(fd,AUD_PWR_CNTRL,TRUE);

	return ret;
}

int gl11_audio_power_off(void)
{
	int ret;
	ret=ioctl(fd,AUD_PWR_CNTRL,FALSE);

	return ret;
}

int gl11_buzz_off(void)
{
	int ret=0;

	ret=ioctl(fd,BUZZER_CNTRL,FALSE);

	return ret;
}
int gl11_buzz_on(void)
{
	int ret=0;

	ret=ioctl(fd,BUZZER_CNTRL,TRUE);

	return ret;
}
int gl11_ifd_control(int val)
{
	int ret=0;

	if(val==0||val==1)
	{
		if(val)
		{
			ret=ioctl(fd,IFD_PWR_CNTRL,TRUE);
			return ret;
		}
		else
		{
			ret=ioctl(fd,IFD_PWR_CNTRL,FALSE);
			return ret;	
		}
	}
	else
	{
		fprintf(stdout,"Enter Valid Input as 0 or 1\n");
		return ARG_ERR;
	}
}

int gl11_cam_control(int val)
{
	int ret=0;

	if(val==0||val==1)
	{
		if(val)
		{
			ret=ioctl(fd,CAM_PWR_CNTRL,TRUE);
			return ret;
		}
		else
		{
			ret=ioctl(fd,CAM_PWR_CNTRL,FALSE);
			return ret;	
		}
	}
	else
	{
		fprintf(stdout,"Enter Valid Input as 0 or 1\n");
		return ARG_ERR;
	}

}

int gl11_bluetooth_control(int val)
{
	int ret=0;

	if(val==0||val==1)
	{
		if(val)
		{
			ret=ioctl(fd,BLUTH_PWR_CNTRL,TRUE);
			return ret;
		}
		else
		{
			ret=ioctl(fd,BLUTH_PWR_CNTRL,FALSE);
			return ret;	
		}
	}
	else
	{
		fprintf(stdout,"Enter Valid Input as 0 or 1\n");
		return ARG_ERR;
	}
}

/*int gl11_gsm_usb_pwr_ctrl(int val)
  {
  int ret=0;

  if(val==0||val==1)
  {
  if(val)
  {
  ret=ioctl(fd,GSM_USB_PWR_CNTRL,TRUE);
  return ret;
  }
  else
  {
  ret=ioctl(fd,GSM_USB_PWR_CNTRL,FALSE);
  return ret;	
  }
  }
  else
  {
  fprintf(stdout,"Enter Valid Input as 0 or 1\n");
  return ARG_ERR;
  }
  }*/

int gl11_sam_pwr_ctrl(int val)
{

	int rv;
	struct stat statBuffer;

	rv = stat("/var/run/pcscd/pcscd.pid", &statBuffer); //added to kill pcscd daemon
	if(rv==0)
	{
		system("kill -9 `pidof pcscd`  > /dev/null 2>&1 ");
		system("rm /var/run/pcscd/*   > /dev/null 2>&1   ");
	}

	int ret=0;

	if(val==0||val==1)
	{
		if(val)
		{
			ret=ioctl(fd,SAM_PWR_CNTRL,TRUE);
			return ret;
		}
		else
		{
			ret=ioctl(fd,SAM_PWR_CNTRL,FALSE);
			return ret;	
		}
	}
	else
	{
		fprintf(stdout,"Enter Valid Input as 0 or 1\n");
		return ARG_ERR;
	}
}

int gl11_magswipe_pwron(void)
{

	return 0;
}

int gl11_magswipe_pwroff(void)	
{
	return 0;
}

int gl11_GetBatteryInfo(int *AdapPresent,int *BattSt,int *BattVt)
{

	int Bat=0,adpt=0,status=0;

	adpt = get_node_readvalue("/sys/devices/platform/imx6q-ecspi.1/spi_master/spi1/spi1.1/bat1");
	if(Bat <0){
		fprintf(stderr,"LIB#Node Read Error\n");
		return -1;
	}

	*AdapPresent = (adpt >1000)?1:0;
	if(adpt > 1000){

		*BattSt = get_batterysense.batsense_val;
	}
	else{
		*BattSt = 0;
	}

	Bat = get_node_readvalue("/sys/devices/platform/imx6q-ecspi.1/spi_master/spi1/spi1.1/bat2");
	if(Bat <0){
		fprintf(stderr,"LIB#Node Read Error\n");
		return -1;



	}
	if(Bat <200)
		*BattVt =0;
	else{
		*BattVt =(Bat/2);

	}
	return 0;
}



int get_node_readvalue(const char *node_name)
{
	int ssk=0, fd1=0;
	short int i=3, j=0;
	char bat[6]="";

	while(i >0)
	{
		if((fd1 = open(node_name, O_RDONLY)) <0){
			fprintf(stderr,"LIB#%s Node File Open Error\n",node_name);
			return -1;
		}
		if((j = read(fd1, bat, 5)) <0){
			fprintf(stderr,"LIB#%s Node File Read Error\n",node_name);
			return -1;
		}
		bat[j] = '\0';
		close(fd1);
		ssk += atoi(bat);
		i--;
	}
	return (ssk/3);
}

int gl11_eth_control (int state)
{
	return 0;
}
int gl11_lcdbklt_time_duration(int val)
{
	int ret;


	if(val <16 || val >90){
		fprintf(stderr,"LIB#Lcd Backlight Timeout Range 16-90 Secs\n");
		return ARG_ERR;
	}

	ret = ioctl(fd, LCD_BKL_TIMEOUT, val);

	if(ret < 0){
		fprintf(stderr,"LIB#Lcd Backlight Timeout ioctl Error \n");
		return -TRUE;
	}
	return 0;
}
int  gl11_touch_buzz_on(void)
{
	int ret;

	ret =  ioctl(fd,TOUCH_BUZZ_CNTRL ,1);
	if(ret < 0){
		fprintf(stderr,"LIB#Touch Buzzer on ioctl Error \n");
		return -1;
	}
	return 0;

}

int  gl11_touch_buzz_off(void)
{
	int ret;

	ret =  ioctl(fd,TOUCH_BUZZ_CNTRL,0);
	if(ret < 0){
		fprintf(stderr,"LIB#Touch Buzzer on ioctl Error \n");
		return -1;
	}
	return 0;

}
int gl11_keypad_buzz_on(void)
{
	int ret;
	ret=ioctl(fd,KEY_BUZZ_CNTRL,1);


	if(ret < 0){
		fprintf(stderr,"LIB#KeyPad Buzzer on ioctl Error \n");
		return -1;
	}
	return 0;


}

int gl11_keypad_buzz_off(void)
{
	int ret;
	ret=ioctl(fd,KEY_BUZZ_CNTRL,0);


	if(ret < 0){
		fprintf(stderr,"LIB#KeyPad Buzzer off ioctl Error \n");
		return -1;
	}
	return 0;


}

int rootfs_details(char *rootfsver)
{
	memset(rootfsver, 0, sizeof(rootfsver));
	system("cat /etc/rc.d/rc.local | grep GL11-RD | cut -c7-31 > /tmp/rootfsver");
	if(Get_String_file("/tmp/rootfsver", rootfsver) <0){
		return -1;
	}
	return 0;
}


int kernel_details(char *kernelver)
{
	int fd,i,j;
	char buff[1048700]="",data[64];
	memset(kernelver, 0 ,sizeof(kernelver));

	fd=open("/dev/mmcblk0",O_RDONLY);
	if(fd < 0){
		fprintf(stderr,"File open error\n");
		return -1;
	}
	if ( 1048576+64 != read(fd,buff,1048576+64))
		return -1;

	for (i=(1048576+32),j=0;i<1048576+62;i++,j++)
		data [j]=buff[i];

	data [j]='\0';
	strcpy(kernelver,data);
	close(fd);
	return 0;
}


int gl11_getuid (char *Uid)
{
	memset(Uid, 0, sizeof(Uid));
	system("cat /proc/cpuinfo | grep Serial | cut -c11-30 > /tmp/uid");
	if(Get_String_file("/tmp/uid", Uid) <0){
		return -1;
	}
	return 0;
}
int Get_String_file(char *Path, char *Line)
{
	FILE* fp=NULL;
	size_t size=0;
	char *str=NULL;

	fp=fopen(Path, "r");
	if(fp==NULL){
		fprintf(stderr,"LIB#%s File Open Error\n",Path);
		fclose(fp);
		return -1;
	}
	getline(&str, &size, fp);
	str[strlen(str)-1]='\0';
	strcpy(Line, str);
	fclose(fp);
	return 0;
}




int bootloader_details(char *Bver)
{
	memset(Bver, 0, sizeof(Bver));
	system("fw_printenv ver | cut -c5-32 > /tmp/Bver");
	if(Get_String_file("/tmp/Bver", Bver) <0){
		remove("/tmp/Bver");
		return -1;
	}
	remove("/tmp/Bver");
	return 0;
}


int gl11_bklight_intensity(int val)
{
	int ret;
	return 0;
}



int gl11_getpinpadid(char *machineid)
{

	unsigned char ch;
	int result=0, i=0;
	FILE *fp=NULL;

	system("fw_printenv  machineid > /tmp/machineid");
	fp = fopen("/tmp/machineid", "rb");
	if(fp ==NULL){
		fprintf(stderr,"LIB#Unable To Open The /tmp/machineid\n");
		return -1;
	}
	for(i=0; i<20; i++)
	{
		ch = fgetc(fp);
		if(i ==0){
			if(ch !='m'){
				result =1;
				break;
			}
		}
		if(i >9)
			machineid[i-10] = ch;
	}
	machineid[10] = 0x00;
	fclose(fp);

	remove("/tmp/machineid");
	if(result){
		fprintf(stderr,"LIB#Machineid Not Found\n");
		return -1;
	}

	return 0;
}

int gl11_getmacid(char *macid)
{
	struct ifreq ifr;
	int fd=0,i=0,eth_flag = 0;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name,"eth0", IFNAMSIZ-1);
	if(ioctl(fd,SIOCGIFHWADDR, &ifr) <0)
	{
		close(fd);
		return -1;
	}
	close(fd);
	memset(macid, 0, sizeof(macid));
	sprintf(macid,"%02X:%02X:%02X:%02X:%02X:%02X",(UC)ifr.ifr_hwaddr.sa_data[0], (UC)ifr.ifr_hwaddr.sa_data[1],
			(UC)ifr.ifr_hwaddr.sa_data[2], (UC)ifr.ifr_hwaddr.sa_data[3],
			(UC)ifr.ifr_hwaddr.sa_data[4], (UC)ifr.ifr_hwaddr.sa_data[5]);
	return 0;
}




int gl11_gethwid(char *hwid)
{

	unsigned char ch;
	int result=0, i=0;
	FILE *fp=NULL;

	system("fw_printenv  hwid > /tmp/hwid");
	fp = fopen("/tmp/hwid","rb");
	if(fp ==NULL)
	{
		fprintf(stderr,"LIB#Unable To Open The /tmp/hwid\n");
		return -1;
	}
	for(i=0; i<20; i++)
	{
		ch = fgetc(fp);
		if(i ==0){
			if(ch !='h'){
				result=1;
				break;
			}
		}
		if(i >4)
			hwid[i-5] = ch;
	}
	hwid[8] = 0x00;
	fclose(fp);
	remove("/tmp/hwid");
	if(result){
		fprintf(stderr,"LIB#Hwid Not Found\n");
		return -1;
	}

	return 0;
}


int gl11_audio_vol_control(int val)
{
        int contrl;
        char buff[100]="";
        if(val<= 130)
                contrl = 130;
        else if(val >= 190)
                contrl = 190;
	else 
	val==contrl;
        sprintf(buff,"amixer cset numid=1 %d",contrl);
        if(system(buff) != 0){
                fprintf(stderr,"Volume control Error\n");
                return -1;
        }

        return 0;

}

