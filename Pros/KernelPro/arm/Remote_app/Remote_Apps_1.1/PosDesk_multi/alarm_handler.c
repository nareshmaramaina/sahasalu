#include<header.h>
void alarmHandler(int signo)
{
	//	static int in=0;
	char cmd[512];
	int num,i;
	int	ret ;


	if ( Foreground_process == 1)
	{
		ret = -3;
		fprintf(stderr,"Still system call is running, Acknowledgment is sending\n");
		write(sockfd,&ret,sizeof(ret));

		ret = wait_for_data(sockfd,120);

		if (ret <= 0 )
		{
			fprintf(stdout,"Foreground error From server, Exiting\n");
			close(sockfd);		
			return;	
		}
		ret =0;
		read(sockfd,&ret,sizeof(ret));
		fprintf(stderr,"Foregorund msg flag = %d\n",ret);
		if ( ret  == 1)
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
		}

		else alarm(60);
	}

	printf("**** Alarm Exiting*****\n");

}
