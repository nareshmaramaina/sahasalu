#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include "Hfont.h"
#include"updated_hex_file_bkp.h"


#define ADC_NO_ADAPTER  500
#define ADC_MIN_BATTERY 830 //Battery reading at 6.8V
#define ADC_HOT_HEAD    300 //NTC Thermistor reading at 75C

#define PRN_ERR         -1
#define PRN_LEN_ERR     -3
#define PRN_BUSY         2
#define PRN_SUCCESS      1 
#define NO_PAPER        -2
#define NO_LINES        -4
#define LOW_BATTERY     -7
#define MAX_TEMP        -8
#define LID_ERROR       -6

#define PRN_OFF     0
#define PRN_ON      1

int prn_write_text(unsigned char *text, int len, int font);

/* Global Variables */
/*Application Should Not Touch These Variables*/
static const char *bat_name="/sys/devices/platform/imx6q-ecspi.1/spi_master/spi1/spi1.1/bat2";
static const char *adapter_name="/sys/devices/platform/imx6q-ecspi.1/spi_master/spi1/spi1.1/bat1";
static const char *thermister_name="/sys/devices/platform/imx6q-ecspi.1/spi_master/spi1/spi1.1/aux3";

static int prn_fd;
static int prnstatus=PRN_OFF, prn_len=0, first_count =0;
static char prn_s[48], pdbl[48], prn_sl[1024*150];

static int strobewidth=0, voltage=0, ther_res=0;
static unsigned char max_temp =0;

struct get_strb{
	int strobewidth_value;
}__attribute__ ((packed));


struct get_strb get_strobewidth;

// For 0 degrees
static int voltage_strobewidth_0[10] ={990, 1091, 1148, 1209, 1275, 1347, 1425, 1510, 1603, 922};
// For 5 degrees
static int voltage_strobewidth_5[10] ={923, 1018, 1071, 1128, 1190, 1257, 1330, 1409, 1496, 861};
// For 10 degrees
static int voltage_strobewidth_10[10] ={863, 952, 1001, 1054, 1112, 1175, 1243, 1313, 1399, 805};
// For 15 degrees
static int voltage_strobewidth_15[10] ={803, 885, 931, 981, 1035, 1093, 1156, 1226, 1301, 749};
// For 20 degrees
static int voltage_strobewidth_20[10] ={749, 826, 869, 915, 966, 1020, 1079, 1143, 1214, 699};
// For 25 degrees
static int voltage_strobewidth_25[10] ={695, 767, 807, 850, 896, 947, 1002, 1061, 1127, 648};
// For 30 degrees
static int voltage_strobewidth_30[10] ={648, 714, 752, 792, 835, 882, 933, 989, 1050, 605};
// For 35 degrees
static int voltage_strobewidth_35[10] ={597, 659, 693, 730, 770, 813, 860, 912, 968, 557};
// For 40 degrees
static int voltage_strobewidth_40[10] ={553, 610, 642, 676, 713, 753, 797, 844, 896, 516};
// For 45 degrees
static int voltage_strobewidth_45[10] ={512, 564, 594, 626, 660, 697, 737, 781, 830, 477};
// For 50 degrees
static int voltage_strobewidth_50[10] ={468, 516, 542, 571, 603, 637, 674, 714, 758, 436};
// For 55 degrees
static int voltage_strobewidth_55[10] ={430, 474, 498, 525, 554, 585, 619, 656, 696, 401};
// For 60 degrees
static int voltage_strobewidth_60[10] ={392, 432, 455, 479, 505, 533, 564, 598, 635, 366};
// For 65 degrees
static int voltage_strobewidth_65[10] ={354, 390, 410, 432, 456, 482, 510, 540, 573, 330};

/*--------------------------------------------------------------------------------------------*/

static int get_node_readvalue(const char *node_name)
{
	int ssk=0, fd=0;
	short int i=3, j=0;
	char bat[6]="";

	while(i >0)
	{
		if((fd = open(node_name, O_RDONLY)) <0){
			fprintf(stderr,"LIB#%s Node File Open Error\n",node_name);
			return -1;
		}
		if((j = read(fd, bat, 5)) <0){
			fprintf(stderr,"LIB#%s Node File Read Error\n",node_name);
			return -1;
		}
		bat[j] = '\0';
		close(fd);
		ssk += atoi(bat);
		i--;
	}
	return (ssk/3);
}

static int prn_vstrobewidth(int val)
{
	if(ther_res >906 && ther_res <932) // 0 to 5
		return voltage_strobewidth_0[val];
	else if(ther_res >877 && ther_res <907) // 5 to 10
		return voltage_strobewidth_5[val];
	else if(ther_res >844 && ther_res <878) // 10 to 15
		return voltage_strobewidth_10[val];
	else if(ther_res >806 && ther_res <845) // 15 to 20
		return voltage_strobewidth_15[val];
	else if(ther_res >768 && ther_res <807) // 20 to 25
		return voltage_strobewidth_20[val];
	else if(ther_res >719 && ther_res <769) // 25 to 30
		return voltage_strobewidth_25[val];
	else if(ther_res >676 && ther_res <720) // 30 to 35
		return voltage_strobewidth_30[val];
	else if(ther_res >626 && ther_res <677) // 35 to 40
		return voltage_strobewidth_35[val];
	else if(ther_res >577 && ther_res <627) // 40 to 45
		return voltage_strobewidth_40[val];
	else if(ther_res >530 && ther_res <578) // 45 to 50
		return voltage_strobewidth_45[val];
	else if(ther_res >480 && ther_res <531) // 50 to 55
		return voltage_strobewidth_50[val];
	else if(ther_res >434 && ther_res <481) // 55 to 60
		return voltage_strobewidth_55[val];
	else if(ther_res >384 && ther_res <435) // 55 to 60
		return voltage_strobewidth_60[val];
	else if(ther_res >341 && ther_res <385) // 60 to 65
		return voltage_strobewidth_65[val];
	else	return 0;
}

static int prn_get_stb_width(void) //Returns required strobe width in uSec based on VH voltage
{

	ther_res = get_node_readvalue(thermister_name);
	//fprintf(stderr,"LIB#Thermister Ret Value: %d\n",ther_res);
	if(ther_res <0) return PRN_ERR;

	ther_res = ther_res /4;
	//fprintf(stderr,"LIB#Thermister/4 Ret Value: %d\n",ther_res);
	if(ther_res <=ADC_HOT_HEAD)
		return 0; //Return "Thermal head too Hot" Temp > 70C

	voltage = get_node_readvalue(adapter_name);
	//fprintf(stderr,"LIB#Adapter Voltage: %d\n",voltage);
	//if(voltage <0) return PRN_ERR;

	voltage = voltage /2;
	if(voltage <ADC_NO_ADAPTER)
	{
		voltage = get_node_readvalue(bat_name);
		//fprintf(stderr,"LIB#Battery Voltage: %d\n",voltage);
		voltage = voltage /2;
		if(voltage <=ADC_MIN_BATTERY)
			return 1; //Return "Battery Too Weak"
		if(voltage >1010) //0:(>1010)
			return prn_vstrobewidth(0);
		else if(voltage >990 && voltage <1011) //1:(991 to 1010)
			return prn_vstrobewidth(1);
		else if(voltage >960 && voltage <991) //2:(961 to 990)
			return prn_vstrobewidth(2);
		else if(voltage >930 && voltage <961) //3:(931 to 960)
			return prn_vstrobewidth(3);
		else if(voltage >910 && voltage <931) //4:(911 to 930)
			return prn_vstrobewidth(4);
		else if(voltage >890 && voltage <911) //5:(891 to 910)
			return prn_vstrobewidth(5);
		else if(voltage >860 && voltage <891) //6:(861 to 890)
			return prn_vstrobewidth(6);
		else if(voltage >840 && voltage <861) //7:(841 to 860)
			return prn_vstrobewidth(7);
		else return prn_vstrobewidth(8); //8:(<841)
	}
	else return prn_vstrobewidth(9); //9:Voltage >500
}

static int prn_reterror(int Error_no)
{
	switch(Error_no)
	{
		case 0x0a: Error_no =-2; //No Paper 10
			   break;
		case 0x06: Error_no =-3; //Memory Error 6
			   break;
		case 0x07: Error_no =-4; //No Lines to Print 7
			   break;
		case 0x08: Error_no =-5; //Write Err 8
			   break;
		case 0x09: Error_no =-6; //Platten Switch(Print Door Open) 9
			   break;
		case 0x0b: Error_no =-7; //Low Battery 11
			   break;
		case 0x0c: Error_no =-8; //Max.Temp 12
			   break;
		default  :break;
	}
	return Error_no;
}

int prn_status(void)
{
	if(get_node_readvalue(thermister_name) >4000){
		fprintf(stdout,"LIB#Printer Not Present\n");
		return PRN_ERR;
	}
	return 0;
}

int prn_open(void)
{
	if(prnstatus ==PRN_ON){
		fprintf(stdout,"LIB#Already Open prn_open\n");
		return PRN_BUSY;
	}
	prn_fd = open("/dev/tpd", O_WRONLY);
	if(prn_fd <0){
		fprintf(stderr,"LIB#Error Opening Device /dev/tpd\n");
		prnstatus = PRN_OFF;
		return PRN_ERR;
	}
	prnstatus = PRN_ON;
	return PRN_SUCCESS;
}

int prn_close(void)
{
	if(prnstatus ==PRN_ON)
	{
		close(prn_fd);
		prnstatus = PRN_OFF;
		return PRN_SUCCESS;
	}
	return PRN_ERR;
}

int prn_paperstatus(void)
{
	int pstat=-2;

	if(prnstatus == PRN_ON) 
		pstat=ioctl(prn_fd, 1, 0);
	return pstat;
}

int prn_lid_status(void)
{
	return ioctl(prn_fd, 7, NULL);
}

int prn_paper_feed(int slines)
{
	//int len=0;
	unsigned char str[3100]="";
	//int feed_array[30] ={52, 103, 154, 205, 256, 307, 358, 409, 460, 511, 562, 613, 664, 715, 766, 817, 868, 919, 970, 1021, 1072, 1123, 1174, 1225, 1276, 1327, 1378, 1429, 1480, 1531}; //Paperfeed Original Scanlines

	if(prnstatus ==PRN_OFF){
		fprintf(stderr,"LIB#2.prn_open Not Open\n");
		return PRN_ERR;
	}
	if(slines <1 || slines >60){
		fprintf(stderr,"LIB#Pass Valid prn_paper_feed(1-60)s\n");
		return NO_LINES;
	}

	if(prn_lid_status() <0){
		fprintf(stderr,"LIB#1.prn_lid_status Error Please Check Lid\n");
		return LID_ERROR;
	}
	if(prn_paperstatus() <0){
		fprintf(stderr,"LIB#1.prn_paperstatus Error\n");
		return NO_PAPER;
	}
	memset(str, 0x00, 3100);
	
#if 0
	ther_res = get_node_readvalue(thermister_name);
	ther_res = ther_res /4;
	if(slines <31)
		len =feed_array[slines -1];
	else	len =slines *51;
	memset(str, 0x00, len);
#endif	
	memset(str, 0x00, 60);
	memset(str, 0x0A, slines);
	ioctl(prn_fd, 10, 0);
	usleep(15);
	//return write(prn_fd, str, len);
	return prn_write_text(str, slines, 1);
}

static void prn_fill_printbuf(int n)
{
	int i=0, j=0;

	if(first_count ==1){
		for(i=0; i<384; i++)
			prn_sl[prn_len++] = 0x00;
		first_count=0;
	}

	for(i=0; i<n; i++)
		for(j=0; j<48; j++)
			prn_sl[prn_len++] = prn_s[j];
}

static void prn_doublewidth(void)
{
	int i=0, j=0;
	unsigned char ch=0;

	for(i=0,j=0; i<24; i++,j+=2)
	{
		ch = pdbl[i] & 0xc0;
		ch |= (pdbl[i] >>2) & 0xc;
		prn_s[j] = ch & 0x88;
		prn_s[j] |= (ch >>1) & 0x66;
		prn_s[j] |= (ch >>2) & 0x11;
		ch = (pdbl[i] << 4) & 0xc0;
		ch |= (pdbl[i] <<2) & 0xc;
		prn_s[j+1] = ch & 0x88;
		prn_s[j+1] |= (ch >>1) & 0x66;
		prn_s[j+1] |= (ch >>2) & 0x11;
	}
	//fprintf(stdout,"LIB#prn_doublewidth: J=%d, i=%d\n",j,i);
}

int prn_write_text(unsigned char *text, int len, int font) //Pass Address and prn_len of string to be Printed
{
	int line_chars=0, i=0, j=0, k=0, r=0, lpos=0, bcnt=0, totallines=0;
	char Text[42*42 +1]="", chr;//Modified Text

	//fprintf(stdout,"LIB#In prn_write_test\n");
	if(prnstatus ==PRN_OFF){
		fprintf(stderr,"LIB#1.prn_open Not Open\n");
		return PRN_ERR;
	}
	if(len <1){
		//fprintf(stderr,"LIB#1.prn_write_text No Lines\n");
		return NO_LINES;
	}
	if(len >42*40){
		//fprintf(stderr,"LIB#2.prn_write_text Length Excceds\n");
		return PRN_LEN_ERR;
	}

	first_count = 1;//Its for V4 Printers

	if(prn_lid_status() <0){
		fprintf(stderr,"LIB#2.prn_lid_status Error Please Check Lid\n");
		return LID_ERROR;
	}

	if(prn_paperstatus() <0){
		fprintf(stderr,"LIB#2.prn_paperstatus Error\n");
		return NO_PAPER;
	}

	if(max_temp ==1){
		ther_res = get_node_readvalue(thermister_name);
		//fprintf(stderr,"LIB#get_node_readvalue() In Max.Temp Thermister: %d\n",ther_res);
		ther_res = ther_res /4;
		if(ther_res >=520)
			max_temp =0;
		else{
			max_temp =0;
			return MAX_TEMP;
		}
	}

	line_chars =(font ==2)?21:42;//Its Value as Charecters for One Line

	for(i=0,j=0; j <=len && i <line_chars*40; i++,j++)//Including '\0'
	{
		if(text[j] !='\n')
			Text[i] = text[j];
		else{
			r = (i+1) % line_chars;
			if(r !=0){
				for(k=0; k <=(line_chars-r) && i <line_chars*30; k++,i++)
					Text[i] =' ';// blank space
				i = i-1;
			}else
				Text[i] =' ';
		}
	}
	len = strlen(Text);
	r = len % line_chars;
	if(r !=0){
		for(i=0; i <(line_chars-r); i++)
			Text[len + i] =' ';// blank space
		Text[len+i] ='\0';
	}else	Text[len] ='\0';

	totallines = strlen(Text) / line_chars; //Characters per line
	//fprintf(stdout,"LIB#No of Character: %d Lines: %d\n",strlen(Text),totallines);

	if(totallines >40){
		fprintf(stderr,"LIB#Input Size Exceeds Lines, Newline Character is Counted as a Line:%d Strlen:%d\n",totallines,strlen(Text));
		return PRN_LEN_ERR;
	}

	prn_len = 0;
	r = 0;//At which Character we are in the given Text
	//fprintf(stdout,"LIB#Width:%d\n",line_chars);
	bzero(prn_sl, 1024*150);
	usleep(100);//Its Added for to Avoided Atomic Error
	for(i =0; i <totallines; i++)//Here i:Textline
	{
		for(j =0; j <17; j++){// Scanlines Per Character
			bzero(prn_s, 48);
			if(line_chars ==21)
				bzero(pdbl, 48);
			usleep(50);//Its Added for to Avoided Atomic Error
			for(k =0, lpos=0, bcnt=0; k <line_chars; k++) //line_chars=42/21 k:Letter
			{
				chr = Hfont_tbl[ (int)Text[ r+k ] ][j];

				if(line_chars ==21)
					pdbl[lpos] |= chr >> bcnt;
				else
					prn_s[lpos] |= chr >> bcnt;
				lpos++;
				if(line_chars ==21)
					pdbl[lpos] |= chr << (8-bcnt);
				else
					prn_s[lpos] |= chr << (8-bcnt);
				bcnt++;
				if(bcnt >=8){
					bcnt=0;
					lpos++;
				}
			}
			if(line_chars <42)
				prn_doublewidth();
			prn_fill_printbuf(3);
		}
		r += line_chars; //line_chars=42/21 characters for next line
	}
	usleep(50);//Its Added for to Avoided Atomic Error
	//fprintf(stdout,"LIB#Printing:%d\n",prn_len);
	strobewidth = prn_get_stb_width();
	get_strobewidth.strobewidth_value = strobewidth;
	if(strobewidth ==0){
		fprintf(stderr,"LIB#1.prn_write_text Max Temp Error\n");
		max_temp =1;
		return MAX_TEMP;
	}
	else if(strobewidth ==1){
		fprintf(stderr,"LIB#1.prn_write_text Low Battery Error\n");
		return LOW_BATTERY;
	}
	if(line_chars ==21)
		ioctl(prn_fd, 0x5, &get_strobewidth);
	else	ioctl(prn_fd, 0x4, &get_strobewidth);

	line_chars = write(prn_fd, prn_sl, prn_len);
	return prn_reterror(line_chars);
}

int prn_write_bmp(unsigned char *bitmap, long len)//bitmap
{
	int bmp_ret=0;

	if(prnstatus ==PRN_OFF){
		fprintf(stderr,"LIB#3.prn_open Not Open\n");
		return PRN_ERR;
	}
	if(len <1){
		//fprintf(stderr,"LIB#1.prn_write_bmp No Lines Error\n");
		return NO_LINES;
	}


 	if(prn_paperstatus() <0){
                fprintf(stderr,"LIB#1.prn_paperstatus Error\n");
                return NO_PAPER;
}


 if(prn_lid_status() <0){
                fprintf(stderr,"LIB#2.prn_lid_status Error Please Check Lid\n");
                return LID_ERROR;
        }



	strobewidth = prn_get_stb_width();
	get_strobewidth.strobewidth_value = strobewidth;
	if(strobewidth ==0){
		fprintf(stderr,"LIB#2.prn_write_bmp Max Temp Error\n");
		max_temp =1;
		return MAX_TEMP;
	}
	else if(strobewidth ==1){
		fprintf(stderr,"LIB#2.prn_write_bmp Low Battery Error\n");
		return LOW_BATTERY;
	}

	bmp_ret = ioctl(prn_fd, 0x6, &get_strobewidth);
	bmp_ret = write(prn_fd, bitmap, len-1);
	return prn_reterror(bmp_ret);
}

int prn_prepare_bmp(unsigned char* Bmpbuf, unsigned char* Data, int Len)
{
	int i=0, j=0;

	for(i=0,j=0; i<Len; i++)
	{
		if(j >29800){
			fprintf(stderr,"LIB#Prepare Bmp Length Error: %d\n",j);
			return PRN_ERR;
		}
		if(i%48 ==0)
			j=j+(48*4);
		Bmpbuf[j+(47-(i%48))] =~Data[i];
		Bmpbuf[j+48+(47-(i%48))] =~Data[i];
		Bmpbuf[j+96+(47-(i%48))] =~Data[i];
		Bmpbuf[j+48+96+(47-(i%48))] =~Data[i];
	}
	return j;
}

int print_test()
{
	int ch;
	char chr[1]="";
	int fd=0,len;
	unsigned char text[1000];
	while(1){

		fprintf(stdout,"\n******GL11 PRINTER MENU********\n\n");
		fprintf(stdout,"1.Printer Open\n");
		fprintf(stdout,"2.Print Text\n");
		fprintf(stdout,"3.Print BMP\n");
		fprintf(stdout,"4.Paper Status\n");
		fprintf(stdout,"5.PrinterLid Status\n");
		fprintf(stdout,"6.Paper Feed\n");
		fprintf(stdout,"7.Printer Close\n");
		fprintf(stdout,"8.Application Exit\n");

		fprintf(stdout,"\nEnter the Feature you want to test\n");
		scanf("%d",&ch);

		switch(ch)
		{

			case 1:
				fd=prn_open();
				if(fd==1)
					printf("Printer Opened Successfully\t\t\n");
				else if(fd==2)
					printf("Printer Already Opened\t\t\n");
				else if(fd==-1)
					printf("Printer Open Failure\t\t\n");
				break;

			case 2:
				printf("Enter the text you need to print\n");
				scanf("%c",chr);
				gets(text);
				fd=prn_write_text(text,sizeof(text),1);
				if(fd==0)
					printf("printer write text success\t\t\n");
				else if(fd==-1)
					printf("printer device not opened\t\t\n");
				else if(fd==-2)
					printf("Text Length Exceeded\t\t\n");
				else if(fd==-4)
					printf("Batter Low\t\t\n");
				else if(fd==-5)
					printf("Maximum Temperature\t\t\n");
				else if(fd==-6)
					printf("No Lines to Print\t\t\n");
				else if(fd==-7)
					printf("Write Error\t\t\n");
				break;
			case 3:
				fd=prn_write_bmp(bmp,sizeof(bmp));
				if(fd==0)
					printf("printer write bmp success\t\n");
				else if(fd==-1)
					printf("printer device not opened\t\n");
				else if(fd==-2)
					printf("Text Length Exceeded\t\n");
				else if(fd==-4)
					printf("Batter Low\t\n");
				else if(fd==-5)
					printf("Maximum Temperature\t\n");
				else if(fd==-6)
					printf("No Lines to Print\t\n");
				else if(fd==-7)
					printf("Write Error\t\n");
				break;

			case 4: fd=prn_paperstatus();
				if(fd==0)
					printf("Printer paper present\t\n");
				else
					printf("Printer Paper not present\t\n");
				break;


			case 5:
				fd=prn_lid_status();

				if(fd==0)
					printf("Printer lid Closed\t\t\n");
				else
					printf("Printer lid  Opened \t\t\n");
				break;

			case 6:

				fd=prn_paper_feed(1);
				if(fd==-1)
					printf("Printer not Opened\t\t\n");
				break;
			case 7: 	
				fd=prn_close();
					
				if(fd>=0)
				{
					printf("Printer Closed Successfully\n");
				}
				else{
					printf("Printer Close Failed\n");
					printf("Printer Not in Open State\n"); 
					return -1;
				}	
				break;

			case 8: printf("Terminating Print Test\n");
				exit(0);
				break;
			default:printf("Invalid Option Selected during Print Test\n");
				break;
		}
	}

	return 0;
}
