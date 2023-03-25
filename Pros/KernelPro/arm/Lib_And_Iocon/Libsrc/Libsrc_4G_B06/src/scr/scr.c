#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <linux/input.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <net/if.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>

#define ERROR    -1
#define SUCCESS   0
#define WERROR    1
#define RMUTE     2
#define T0VER     3
#define ERR_LRC   4
#define PRESENT   1
#define NPRESENT -2

static int smart_ifd_fd;
static unsigned char ifd_atr_response[50]="";
static unsigned int ifd_atr_rlen=0;

typedef struct
{
	unsigned long handle;
	unsigned char baud;
	unsigned bits;
	int stopbits;
	char parity;
	unsigned long blocktime;
}IOPORT;

IOPORT ioport;


static int SCR_Baudrate(void)
{
	char Resp[25]="", Cmd[6] ={0x60,0x00,0x01,0x6A,0x01,0x0A};
	int i=0, ret=0;

	fprintf(stdout,"LIB#BaudRate_Read Returns Values(5): ");
	for(i=0; i<5; i++){
		if(write(smart_ifd_fd, Cmd, 6) !=6)
			perror("Write");
		sleep(1);
		ret = read(smart_ifd_fd, Resp, sizeof(Resp));
		fprintf(stdout,"%d ",ret);
		if(!strcmp(Resp, "Baudrate Set")){
			fprintf(stdout,"\nLIB#Baudrate Set Success:===>%d",i);
			break;
		}
		else if(!strcmp(Resp, Cmd)){
			fprintf(stdout,"\nLIB#This Baudrate is Already Set:===>%d",i);
			break;
		}
	}
	fprintf(stdout," \n");
	//SCR_Powerdown();
	if(i >4 || ret<0){
		fprintf(stderr,"LIB#Baudrate Setting Time Out/Set Fail\n");
		return ERROR;
	}
	return SUCCESS;
}

static int SCR_SetTimeOut(unsigned long blocktime)
{
	ioport.blocktime = (unsigned long)blocktime;
	return ioport.blocktime;
}

static unsigned char SCR_Checksum(unsigned char *Data, unsigned int Len)
{
	unsigned short int i;
	unsigned char LRC = 0x00;

	for(i=0; i<Len; i++)
		LRC ^= Data[i];
	return (LRC);
}

static unsigned char GetLRC(unsigned char *Data, unsigned int Offset)
{
	return Data[Offset];
}

static short int TestLRCs(unsigned char LRC_1, unsigned char LRC_2)
{
	if(LRC_1 == LRC_2)
		return SUCCESS;
	return ERR_LRC;
}

static void SCR_CAPDUMake(unsigned char *HexData, unsigned char *ProtoData, unsigned short int *Len)
{
	unsigned char LRC ;
	unsigned short int i=0;

	ProtoData[ 0 ] = 0x60;
	ProtoData[ 1 ] =((*Len)/256);
	ProtoData[ 2 ] =((*Len)%256); 

	fprintf(stdout,"LIB#:===>CAPDU:%02x  %02x<===:\n ",HexData[0],*Len);

	if((HexData[0]==0x00)||(HexData[0]==0x80)||(HexData[0]==0x84)||(HexData[0]==0x8C)||(HexData[0]==0x0C)||(HexData[0]==0x0D))
	{
		ProtoData[3]=0x00;  
		for(i=0; i<(*Len); i++)
			ProtoData[ i+4] = HexData[i];  //formation of prtocol
		LRC= SCR_Checksum(ProtoData,(unsigned short int) (4+ (*Len))); //compute LRC
		ProtoData[i+4]= LRC;
		*Len=5+(*Len);
	}
}

static int SCR_Strip(unsigned char *Sresp, unsigned int *Slen)
{
	int i=0;

	if(Sresp[0]!=0x60){
		*Slen=1;	
		return ERROR;
	}else{
		*Slen=((*Slen)-5);
		for(i=0;i<(*Slen);i++)
			Sresp[i]=Sresp[i+4];	
		return SUCCESS;
	}
}

static int SCR_Send(unsigned char *Cmd, unsigned short int Wsize)
{
	unsigned long handle;
	int res=0;

	handle = ioport.handle;
	fprintf(stdout,"LIB#HANDLE WRITE: %d \n",(int)handle);
	if(tcflush(handle, TCIOFLUSH) <0){
		fprintf(stderr,"LIB#Unable to Flush form Write Error\n");
		return WERROR;
	}
	tcflush(handle, TCOFLUSH); 

	fprintf(stdout,"LIB#Before Write Command: ");
	for(res=0; res<Wsize; res++)
		fprintf(stdout,"%02X ",Cmd[res]);	
	res = write(handle, Cmd, Wsize);
	fprintf(stdout,"\nLIB#:Write Bytes: %d \n",res);
	if(res != Wsize){
		fprintf(stderr,"LIB#Unable to Write Error\n");
		return WERROR;
	}
	fprintf(stdout,"LIB#After Write Command\n");
	return SUCCESS;
}

static int SCR_Read(unsigned char *Rresp, unsigned int *RLen)
{
	unsigned long handle;
	int i=0, rlen=0, bytesread=0, tout=0, recv_stat=0;
	unsigned char ch;
	char *resp=NULL;
	resp=(char*)malloc(512);

	handle=ioport.handle;
	fprintf(stdout,"LIB#HANDLE READ: %d \n",(int)handle);
	while(tout <50 && recv_stat <5)
	{
		i = read(handle, &ch, 1);
		if(i <1){
			tout++;
			//usleep(500000);
			usleep(150000);
			continue;
		}
		tout=0;
		switch(recv_stat)
		{
			case 0: if(ch ==0x60 || ch ==0xe0){
					recv_stat=1;
					bytesread=0;
					rlen=0;
					resp[bytesread]=ch;
					bytesread++;
				}
				break;

			case 1: resp[bytesread]=ch;
				bytesread++;
				recv_stat=2;
				break;

			case 2: resp[bytesread]=ch;
				rlen = resp[bytesread-1]*0x100 + ch +1;
				bytesread++;
				recv_stat=3;
				break;

			case 3: if(rlen >0){
					resp[bytesread]=ch;
					bytesread++;
					rlen--;
					if(rlen ==0)
						recv_stat=4;
				}
				break;

			case 4: resp[bytesread]=ch;
				bytesread++;
				recv_stat=5;
				break;

			default:break;
		}
	}
	tcflush(handle, TCIOFLUSH);
	if(tout >49){
		fprintf(stderr,"LIB#Unable to Read In-Time(10):%02X Received Bytes:%d Error\n",ch,bytesread);
		free(resp);
		return T0VER;
	}
	
	*RLen=bytesread;
	fprintf(stdout,"LIB#After Read Received(Bytes/Data):[%d] ",bytesread);
	for(i=0; i<bytesread; i++){
		Rresp[i] = resp[i];
		fprintf(stdout,"%02X ",Rresp[i]);
	}
	fprintf(stdout," \n");
	free(resp);
	if(Rresp[0] ==0xE0)
		return ERROR;
	return SUCCESS;
}

static int SCR_SendReceive(unsigned char *CommandData, unsigned int CLen, unsigned char *samifd_response_data, unsigned int *ResponseLen)
{
	int retry=0;
	unsigned short int Len=0;
	unsigned char ProtoData[300]="";
	*ResponseLen=0;

	while(retry<3)
	{
		Len=CLen;
		if(CommandData[0]==0x80){
			retry=4;
		}
		SCR_CAPDUMake(CommandData, ProtoData, &Len);
		fprintf(stdout,"LIB#Len: %02x \n",Len);
		if(SCR_Send(ProtoData, Len) ==WERROR)
			return ERROR;
		if(CommandData[0]==0x80){
			fprintf(stderr,"LIB#:================> Command 80 <================: \n");
		}
		SCR_SetTimeOut(10);
		*ResponseLen=0;
		if(SCR_Read(samifd_response_data, ResponseLen) !=0)// Read the Corresponding response from the  Card.
			retry++;	
		if(samifd_response_data[0]==0x60){
			if((samifd_response_data[2]==0x00)&&(samifd_response_data[1]==0x00)){
				retry=4;
				fprintf(stderr,"LIB#Len is Zero:%d\n",retry);
			}
			else
				retry=4;
		}
		if((samifd_response_data[0]==0xE0)||(samifd_response_data[0]==0xe0)){
			retry++;
			if((samifd_response_data[4]==0xC0)||(samifd_response_data[4]==0xc0))
				retry=4;
			if((samifd_response_data[4]==0xFF)||(samifd_response_data[4]==0xff)){
				retry++;
				fprintf(stdout,"LIB#Retry FF:%d\n",retry);
			}
		}
		else if((samifd_response_data[2]!=0x00) || (samifd_response_data[1] != 0x00))
		{
			if(TestLRCs(SCR_Checksum(samifd_response_data, *ResponseLen-1), GetLRC(samifd_response_data, *ResponseLen-1)) !=0)
				retry++;	
			else
				retry=4;
		}
	}
	if(samifd_response_data[0] !=0x60)
		return samifd_response_data[4];
	return SCR_Strip(samifd_response_data, ResponseLen);
}

//****************************USER USAGE FUNCTIONS****************************/
int SCR_Open(void)
{
	struct termios tty_attributes;

	memset(&tty_attributes, 0, sizeof(struct termios));

#ifdef PC
	smart_ifd_fd = open("/dev/ttyS1", O_RDWR | O_NOCTTY | O_NONBLOCK | O_ASYNC);
#else
	smart_ifd_fd = open("/dev/ttymxc3", O_RDWR | O_NOCTTY | O_NONBLOCK);// | O_ASYNC);
#endif
	fprintf(stdout,"LIB#Node:/dev/ttymxc3 Ret:%d\n",smart_ifd_fd);
	if(smart_ifd_fd <0){
		fprintf(stderr,"LIB#Unable to Open Port \nLIB#Please Check The Arguments\n");
		return ERROR;
	}

	tcflush(smart_ifd_fd, TCIOFLUSH);
	tty_attributes.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
	tty_attributes.c_cc[VMIN]=0;
	tty_attributes.c_cc[VTIME]=0;
	
	tcsetattr(smart_ifd_fd, TCSANOW, &tty_attributes);
	ioport.handle = smart_ifd_fd;
	if(SCR_Baudrate() <0){
		fprintf(stdout,"LIB#Please Check Baudrate\n");
		SCR_Close();
		return ERROR;
	}
	return smart_ifd_fd;
}

int SCR_Close(void)
{
	unsigned long static handle;

	handle=ioport.handle;
	fprintf(stdout,"LIB#HANDLE Close: %d \n",(int)handle);
	if(!handle)
		close(handle);	
	return SUCCESS;	
}

int SCR_Selectcard(int card)//Select a Cards
{
	unsigned char Selcmd[10] = {0x60, 0x00, 0x01, 0x6A};
	unsigned char ifd_response[300]="";
	unsigned int Rlen=0;

	memset(ifd_response, 0, 300);

	//Its Change for Pos Cabinate Lables
	Selcmd[4]=(card ==3)?4:(card ==4)?3:card;//Added Card Number

	Selcmd[5] = SCR_Checksum(Selcmd, 5);

	if(SCR_Send(Selcmd, 6) !=0)
		return ERROR;
	if(SCR_Read(ifd_response, &Rlen) !=0)
		return ERROR;
	return SUCCESS;
}

int SCR_Powerup(int volt)//Voltage Apply for Cards
{
	unsigned char Vcmd[10]={0x60, 0x00, 0x00, 0x6E};//Its for 5Volts as Default
	unsigned char ifd_response[300]="";
	unsigned int Rlen=0;
	
	fprintf(stdout,":===>Powerup: %s Volts<===: \n",volt==0?"1.8":volt==1?"3":"5");
	if(volt ==0)//Its for 1.8Volts
		Vcmd[3]=0x6F;
	else if(volt ==1)//Its for 3Volts
		Vcmd[3]=0x6D;

	ifd_atr_rlen =0;//Its For Getatr Response Length
	Vcmd[4] = SCR_Checksum(Vcmd, 4);
	if(SCR_Send(Vcmd, 5) !=0)
		return WERROR;
	SCR_SetTimeOut(0x01);
	Rlen=0;
	memset(ifd_response, 0, 300);
	if(SCR_Read(ifd_response, &Rlen) !=0)
		return ERROR;
	if(SCR_Strip(ifd_response, &Rlen) ==0){
		memcpy(ifd_atr_response, ifd_response, Rlen);//Its For Getatr Response
		ifd_atr_rlen = Rlen;//Its For Getatr Response Length
		return SUCCESS;
	}
	return ERROR;
}

int SCR_Getatr(unsigned char *Aresp, unsigned int *Alen)
{
	if(ifd_atr_rlen <1)
		return ERROR;
	memcpy(Aresp, ifd_atr_response, ifd_atr_rlen);
	*Alen = ifd_atr_rlen;
	return SUCCESS;
}

int SCR_Checkup_Cardpresence(void)
{
	unsigned char Ccp_cmd[10]={0x60, 0x00, 0x00, 0x09};
	unsigned char ifd_response[300]="";
	unsigned int Rlen=0;
	
	memset(ifd_response, 0, 300);

	Ccp_cmd[4] = SCR_Checksum(Ccp_cmd, 4);

	if(SCR_Send(Ccp_cmd, 5) !=0)
		return ERROR;
	if(SCR_Read(ifd_response, &Rlen) !=0)
		return ERROR;
	if(ifd_response[0] == 0xE0)
		return NPRESENT;//return 12; for 92/94POS
	return PRESENT;//return 11; for 92/94POS
}

int SCR_Sendcommand(unsigned char *Cmd, int CLen, unsigned char *Resp, unsigned int *RLen)//Write Command Then Get Response
{
	unsigned int len=0;

	SCR_SendReceive(Cmd, CLen, Resp, &len);
	*RLen = len;
	Resp[len]='\0';
	if(len >0 && Resp[len-2] ==0x90 && Resp[len-1] ==0x00)
		return SUCCESS;
	return ERROR;
}

int SCR_Powerdown(void)//Power Down for Cards
{
	unsigned char Pcmd[10]={0x60, 0x00, 0x00, 0x4D, 0x2D};
	unsigned char ifd_response[300]="";
	unsigned int Rlen=0;

	if(SCR_Send(Pcmd, 5) !=0)
		return ERROR;

	memset(ifd_response, 0, 300);
	if(SCR_Read(ifd_response, &Rlen) !=0){
		fprintf(stderr,"LIB#Power Down Error\n");
		return ERROR;
	}
	return SUCCESS;
}

int SCR_Getlpa(unsigned char *Lresp, unsigned int *Llen)
{
	unsigned char Lpa_cmd[10]={0x60, 0x00, 0x00, 0xEF};

	fprintf(stdout,"LIB#Running Loop Back Application\n");
	Lpa_cmd[4] = SCR_Checksum(Lpa_cmd, 4);

	if(SCR_Send(Lpa_cmd, 5) !=0)
		return WERROR;
	SCR_SetTimeOut(0x01);
	fprintf(stdout,"LIB#Header:RUNNING LOOP BACK APPLICATION A\n");

	if(SCR_Read(Lresp, Llen) !=0)
		return ERROR;
	return SCR_Strip(Lresp, Llen);
}

int SCR_Getlpb(unsigned char *Lresp, unsigned int *Llen)
{
	unsigned char Lpb_cmd[10]={0x60, 0x00, 0x00, 0xEE};

	fprintf(stdout,"LIB#Running Loop Back Application\n");
	Lpb_cmd[4] = SCR_Checksum(Lpb_cmd, 4);

	if(SCR_Send(Lpb_cmd, 5) !=0)
		return WERROR;
	SCR_SetTimeOut(0x01);
	sleep(1);
	fprintf(stdout,"LIB#Header:RUNNING LOOP BACK APPLICATION B\n");

	if(SCR_Read(Lresp, Llen) !=0)
		return ERROR;
	return SCR_Strip(Lresp, Llen);
}

int SCR_Getsb(unsigned char *Sresp, unsigned int *Slen)
{
	unsigned char Sb_cmd[10]={0x60, 0x00, 0x00, 0xCC};

	fprintf(stdout,"LIB#Software Build Number\n");
	Sb_cmd[4] = SCR_Checksum(Sb_cmd, 4);

	if(SCR_Send(Sb_cmd, 5) !=0)
		return ERROR;
	SCR_SetTimeOut(0x01);

	if(SCR_Read(Sresp, Slen) !=0)
		return ERROR;
	return SCR_Strip(Sresp, Slen);
}

int SCR_Getfv(unsigned char *Fresp, unsigned int *Flen)
{
	unsigned char Fv_cmd[10]={0x60, 0x00, 0x00, 0x0A};

	fprintf(stdout,"LIB#Firmwarw Version\n");
	Fv_cmd[4] = SCR_Checksum(Fv_cmd, 4);

	if(SCR_Send(Fv_cmd, 5) !=0)
		return ERROR;
	SCR_SetTimeOut(0x01);

	if(SCR_Read(Fresp, Flen) !=0)
		return ERROR;
	return SCR_Strip(Fresp, Flen);
}

int SCR_Getsn(unsigned char *Sresp, unsigned int *Slen)
{
	unsigned char Sn_cmd[10]={0x60, 0x00, 0x00, 0xAA};

	fprintf(stdout,"LIB#Get Serial Number\n");
	Sn_cmd[4] = SCR_Checksum(Sn_cmd, 4);

	if(SCR_Send(Sn_cmd, 5) !=0)
		return ERROR;
	SCR_SetTimeOut(0x01);

	if(SCR_Read(Sresp, Slen) !=0)
		return ERROR;
	return SCR_Strip(Sresp, Slen);
}

int SCR_Getsn8(unsigned char *Iresp, unsigned int *Ilen)
{
	unsigned char Ifd_cmd[10]={0x60, 0x00, 0x00, 0xBB};

	fprintf(stdout,"LIB#Get Ifd(SN8) Serial Number\n");
	Ifd_cmd[4] = SCR_Checksum(Ifd_cmd, 4);

	if(SCR_Send(Ifd_cmd, 5) !=0)
		return ERROR;
	SCR_SetTimeOut(0x01);

	if(SCR_Read(Iresp, Ilen) !=0)
		return ERROR;
	return SCR_Strip(Iresp, Ilen);
}

int SCR_Ferase(void)
{
	unsigned char Ifd_cmd[10]={0x60, 0x00, 0x00, 0x7A};

	fprintf(stdout,"LIB#Flash_Erased\n");
	Ifd_cmd[4] = SCR_Checksum(Ifd_cmd, 4);

	if(SCR_Send(Ifd_cmd, 5) !=0)
		return ERROR;
	return SUCCESS;
}

//****************************USER USAGE BACKWORD COMPATIBLE FUNCTIONS****************************/
//Its Functions Added For Backward Compaitable by SunSon 05/07/13

int scr_open(void)
{
	return SCR_Open();
}

int scr_close(void)
{
	return SCR_Close();
}

int select_card(int card)
{
	//Its Change for Pos Cabinate Lables
	return SCR_Selectcard(((card ==3)?4:(card ==4)?3:card));
}

int powerup_5v(void)
{
	return SCR_Powerup(2);
}

int powerup_3v(void)
{
	return SCR_Powerup(1);
}

int powerup1_8v(void)
{
	return SCR_Powerup(0);
}

int powerdown(void)
{
	return SCR_Powerdown();
}

int SCR_getATR(unsigned char *Aresp, unsigned int *Alen)
{
	return SCR_Getatr(Aresp, Alen);
}

int SCR_Checkup_CardPresence(void)
{
	short int ret=0;
	
	ret = SCR_Checkup_Cardpresence();
	return ((ret ==1)?11:(ret ==-2)?12:-1);
}

//int SCR_SendCommand(unsigned char *CAPDU_Data, int CLen, unsigned char *RAPDU_Data, unsigned int *RLen)
int SCR_SendCommand(unsigned char *CAPDU_Data, unsigned char CLen, unsigned char *RAPDU_Data, unsigned int *RLen)
{
	if(SCR_SendReceive(CAPDU_Data, CLen, RAPDU_Data, RLen) ==0)
		return SUCCESS;
	return ERROR;
}

int SCR_GetFV(unsigned char *Fv_Resp, unsigned int *Fv_RLen)
{
	return SCR_Getfv(Fv_Resp, Fv_RLen);
}

int SCR_GetSB(unsigned char *Sresp, unsigned int *Slen)
{
	return SCR_Getsb(Sresp, Slen);
}


