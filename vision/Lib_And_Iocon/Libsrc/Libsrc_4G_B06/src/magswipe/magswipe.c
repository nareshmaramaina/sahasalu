#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <string.h>
#define TIME_OUT      -2

#define MAG_SW_ERR	-1
#define MSCR_OFF	 0
#define MSCR_ON		 1
#define MSCR_BUSY	 2
#define MSCR_FAIL	 0
#define MSCR_SUCCESS 1

#define MSCR_TRACK1		 1
#define MSCR_TRACK2		 2
#define MSCR_TRACK3		 3
#define MSCR_TRACK12	 4
#define MSCR_TRACK23	 5
#define MSCR_TRACK13	 6
#define MSCR_TRACK123	 7

#define TRUE		 1
#define FALSE		 0
#define PWRDN_BS300  0x06
static int flagAlarm=0;
//Application Should Not Touch This Variable
static int mscr_fd, mstatus = MSCR_OFF; 

int mscr_open(void)
{
	if(mstatus !=MSCR_OFF){
		fprintf(stderr,"LIB#Magnetic Swipe Already Open\n");
		return MSCR_BUSY;
	}

	mscr_fd = open("/dev/mscrd", O_RDONLY);
	if(mscr_fd <0){
		fprintf(stderr,"LIB#Error:Opening Device /dev/mcsr\n");
		mstatus = MSCR_OFF;
		return MAG_SW_ERR;
	}
	mstatus = MSCR_ON; 
	return MSCR_SUCCESS;
}

int mscr_init(void)
{
#if 0
	gl11_pwrdnbs300(FALSE);
	usleep(10000);
	gl11_pwrdnbs300(TRUE);
	usleep(10000);
#endif
	return 0;
}
int ASCII_TO_BCD(unsigned char *ascii_text,int tr_len,unsigned char *bcd_value,int *bcd_len)
{
        int k=0,j=0,i=0;


        for(i=0;i<tr_len;j++)
        {


                if(ascii_text[k] >= '0' && ascii_text[k] <= '9')  // 0-9 range
                {
                        bcd_value[j] = ( ascii_text[k] - 48)  << 4 ; // 48 for '0' ASCII offset
                }
                else if (ascii_text[k] >= 'A' && ascii_text[k] <= 'F') // A-F range
                {
                        bcd_value[j] = ( 10 + ascii_text[k] - 65 )  << 4 ; // 65 for 'A' ASCII offset
                }
                else if (ascii_text[k] >= 'a' && ascii_text[k] <= 'f') // a-f range
                {
                        bcd_value[j] = ( 10 + ascii_text[k] - 97)  << 4 ; // 97 for 'a'  ASCII offset
                }

                if(ascii_text[k+1] >= '0' && ascii_text[k+1] <= '9')  // 0-9 range
                {
                        bcd_value[j] |= ( ascii_text[k+1] - 48); // 48 for '0' ASCII offset
                }
                else if (ascii_text[k+1] >= 'A' && ascii_text[k+1] <= 'F') // A-F range
                {
                        bcd_value[j] |= ( 10 + ascii_text[k+1] - 65)   ; // 65 for 'A' ASCII offset
                }
                else if (ascii_text[k+1] >= 'a' && ascii_text[k+1] <= 'f') // a-f range
                {
                        bcd_value[j] |= ( 10 + ascii_text[k+1] - 97 ) ; // 97 for 'a' ASCII offset
                }

                i+=2;
                k+=2;

        }

        *bcd_len = j;

        return 0;
}
void HexToAsc (unsigned char *outp, unsigned char *inp, int iLength)
{
        int i;

        for (i = 0; i < iLength; i++)
        {
                if ((inp[i] >> 4) > 9)
                        outp[i * 2] = (unsigned char)((inp[i] >> 4) + 'A' - 10);
                else
                        outp[i * 2] = (unsigned char)((inp[i] >> 4) + '0');

                if ((inp[i] & 0x0f) > 9)
                        outp[i * 2 + 1] = (unsigned char)((inp[i] & 0x0f) + 'A' - 10);
                else
                        outp[i * 2 + 1] = (unsigned char)((inp[i] & 0x0f) + '0');

        }
        outp[i * 2] = 0;

        return;
}

void mscrTimeout(int unused)
{
        flagAlarm = 1;
}

int mscr_getstate_timeout(int timeout)
{
        int ret = 0;
        char state[3]={0x00};
        struct sigaction sa;
        if( mstatus == MSCR_OFF )
                return MAG_SW_ERR;

        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sa.sa_handler = mscrTimeout;
        if (sigaction(SIGALRM, &sa, NULL) == -1)
                perror("sigaction");

        alarm(timeout);
        while(1)
        {
                ret = read(mscr_fd, &state, 3);
                usleep(10000);
                if (ret < 0 ) {
                        perror("Error: Reading MagSwipe State\n");
                        return MAG_SW_ERR;
                }
                if(state[0] ==1)
                {
                        flagAlarm = 0;
                        alarm(0);
                        break;
                }
                if(flagAlarm ==1)
                {
                        flagAlarm = 0;
                        return TIME_OUT;
                }
        }

        return state[0];
}

int mscr_close(void)
{
	if(mstatus ==MSCR_ON){
		close(mscr_fd);
		mstatus = MSCR_OFF;
		//gl11_pwrdnbs300(FALSE);
		return MSCR_SUCCESS;
	}
	return MAG_SW_ERR;
}

int mscr_getstate(void) 
{
	int ret=0;
	char state[3]="";

	if(mstatus ==MSCR_OFF){
		//fprintf(stderr,"LIB#1.Magnetic Swipe Not Open\n");
		return MAG_SW_ERR;
	}
	ret = read(mscr_fd, &state, 3);
	usleep(10000);
	if(ret <0){
		perror("LIB#Error: Reading Magswipe State");
		return MAG_SW_ERR;
	}
	return state[0];
}	

int mscr_flush(void)
{
	if(mstatus ==MSCR_OFF){
		//fprintf(stderr,"LIB#3.Magnetic Swipe Not Open\n");
		return MAG_SW_ERR;
	}
	if(read(mscr_fd, NULL, 0) <0){
		//fprintf(stderr,"LIB#Flushing Magnetic Swipe Card Reader Buffer Error\n");
		return MAG_SW_ERR;
	}
	return MSCR_SUCCESS;
}

int mscr_read(char *track_1_data, char *track_2_data, char *track_3_data)
{	
	int ret1=0, ret2=0, ret3=0;

	if(mstatus ==MSCR_OFF){
		//fprintf(stderr,"LIB#2.Magnetic Swipe Not Open\n");
		return MAG_SW_ERR;
	}
	ret1 = read(mscr_fd, track_1_data, 501);
	ret2 = read(mscr_fd, track_2_data, 502);
	ret3 = read(mscr_fd, track_3_data, 503);

	mscr_flush();

	if(ret1 ==0  && ret2 ==0 && ret3 ==0) 
		return MSCR_TRACK123;
	else if(ret1 ==0 && ret3 ==0)
		return MSCR_TRACK13;
	else if(ret2 ==0 && ret3 ==0)
		return MSCR_TRACK23;
	else if(ret1 ==0 && ret2 ==0)
		return MSCR_TRACK12;
	else if(ret3 ==0)
		return MSCR_TRACK3;
	else if(ret2 ==0)
		return MSCR_TRACK2;
	else if(ret1 ==0)
		return MSCR_TRACK1;
	else
		return MAG_SW_ERR;
}
int mscr_track_encryptdata_DES(unsigned int desk_index ,char *track_1_data,char *hex_enc_data, unsigned char *PAN,int *pan_length)
{

	int ret1,ret2,res;
	FILE *fp;
	int i=0;
	unsigned char bcd_enc_track_2_data[502]="";
	char track_2_data[502]="";
	char mod_track2_data[502]="";
	unsigned char data[502]="";
	unsigned char  bcddata[255]="";
	unsigned char hsk_enc_data[255]="";
	unsigned char HSK[24]={0x22,0x55,0x11,0x11,0x11,0x11,0x11,0x11,
		0x22,0x22,0x22,0x77,0x22,0xaa,0x00,0x22,
		0x33,0x33,0x33,0x33,0x33,0x33,0x44,0x99};
	char *ptr;
	int LEN=0;

	int TRACK2_LEN,bcd_len;
	if( mstatus == MSCR_OFF )
		return MAG_SW_ERR;

	ret1 = read(mscr_fd, track_1_data, 501);

	ret2 = read(mscr_fd, track_2_data, 502);

	if (ret2 == -1 && ret1==0)

		return MSCR_TRACK1 ;
	if (ret2 == -1 && ret1==-1)
		return MAG_SW_ERR ;

	for(i=1;i<=19;i++)
	{
		if(track_2_data[i] == 0x3D)
			break;
		PAN[i-1] = track_2_data[i];

	}
	PAN[i]='\0';
	*pan_length=i-1;

	for(i=0;i<=strlen(track_2_data);i++)
	{
		if(track_2_data[i] == 0x3F)
			break;
		mod_track2_data[i] = track_2_data[i];
	}
	mod_track2_data[i]='\0';

	ptr=strchr(mod_track2_data,'=');
	*ptr='D';
	memset(track_2_data,0x00,sizeof(track_2_data));
	memcpy(track_2_data,mod_track2_data+1,strlen(mod_track2_data)-1);

	LEN = (40-(strlen(track_2_data)));   
	memcpy(data,track_2_data,(strlen(track_2_data)));
	int len=(strlen(track_2_data));
	for(i=0;i<LEN;i++)
		data[len+i]=0 ;

	ASCII_TO_BCD (data,40,bcddata,&bcd_len);
	sdk_3des_ecb(bcddata,24 ,HSK,hsk_enc_data, 1);
	int resp=Get_Des_EncDec_Data (hsk_enc_data, 24 , desk_index,bcd_enc_track_2_data,1);
	res = print_error_resp (resp);
	if (res != 0)
	{
		printf ("Get_Encrypted_track_data Failed\n");
	}
	HexToAsc(hex_enc_data,bcd_enc_track_2_data,24);
	mscr_flush();
	if (ret1 == 0 && ret2 == 0)
		return MSCR_TRACK12 ;
	else if (ret2 == 0)
		return MSCR_TRACK2 ;
	else if (ret1 == 0)
		return MSCR_TRACK1 ;

	else
		return  MAG_SW_ERR;
}

/*
int magswipe_test()
{
	char track1[256]="",track2[256]="",track3[256]="";
	int ret=0,opt=0;
	while(1)
	{

		fprintf(stdout,"\n*****GL11 MAGSWIPE MENU******\n");	
		fprintf(stdout," 1. Magswipe Open\n");
		fprintf(stdout," 2. Flush Magswipe \n");
		fprintf(stdout," 3. Magswipe Status,Read Track Data\n");
		fprintf(stdout," 4. Magswipe Close\n");
		fprintf(stdout," 5. Application Exit\n");
		
		fprintf(stdout,"Enter the Option You Want to Test\n");
		scanf("%d",&opt);
		switch(opt)
		{	
			case 1:
				ret=mscr_open();
				if(ret==1)
				{
					printf("Magnetic Reader Opened Successfully:%d\n",ret);
				}
				else
				{
					printf("Magnetic Reader Open Failed:%d\n",ret);
					return -1;
				}

				break;
			case 2:

				memset(track1,0x00,256);
				memset(track2,0x00,256);
				memset(track3,0x00,256);

				ret=mscr_flush();
				if(ret==0)
					fprintf(stdout,"Card Format Success\n");
				else
					fprintf(stderr,"Card Format Error\n");

				break;
			case 3:
				memset(track1,0x00,256);
				memset(track2,0x00,256);
				memset(track3,0x00,256);

				ret=mscr_getstate();
				printf("RET FOR STATE:%d\n",ret);
				if(ret>=0)
				{
					printf("Swipe the Card to get Track Data\n");
					sleep(4);
					ret=mscr_read(track1,track2,track3);
					if(ret!=-1)
					{
						fprintf(stdout,"Track1 details %s\n",track1);
						fprintf(stdout,"Track2 details %s\n",track2);
						fprintf(stdout,"Track3 details %s\n",track3);
					}
					system("date\n");

				}
				break;

			case 4:		ret=mscr_close();
					if(ret==1)
					{
						printf("Magnetic Reader Closed Successfully:%d\n",ret);
					}
					else
					{
						printf("Magnetic Reader Close Failed:%d\n",ret);
						return -1;
					}


					break;
			case 5:
					printf("Terminating the MagSwipe Test\n");
					exit(0);
					break;	
			default:printf("Selected Invalid Option\n");
				break;	
		}
	}
}*/
