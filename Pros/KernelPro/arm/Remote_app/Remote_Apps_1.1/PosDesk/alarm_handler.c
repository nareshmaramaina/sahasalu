#include<header.h>
void alarmHandler(int signo)
{
	static int in=0;
	char cmd[512];
	int num,i;
	int	ret ;

	if ( ++in >= 2)
	{
		
		memset(cmd,0,sizeof(cmd));

		if(	strstr(Check_CmD,"/") != NULL ) 
		{
			for(i=0, num=0;i < strlen(Check_CmD);i++)
			{
				if(Check_CmD[i] == '/')
					num=i;
			}
		sprintf(cmd,"kill -9 `pidof %s`",Check_CmD+num+1);
		}
		
		else 
		sprintf(cmd,"kill -9 `pidof %s`",Check_CmD);


		printf(" In alaram cmd = %s,ret =  %d",cmd,system(cmd));
		in=0;	
	}

	if ( Foreground_process == 1)
	{
		ret = -3;
		fprintf(stderr,"Still system call is running, Acknowledgment is sending\n");
		write(sockfd,&ret,sizeof(ret));
		alarm(60);
	}

	printf("**** Alarm Exiting*****\n");

}
