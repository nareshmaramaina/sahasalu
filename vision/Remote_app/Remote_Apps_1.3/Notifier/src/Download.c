#include<header.h>
void Wait_for_internet(void)
{
	int ret_value=0;
	while(1)
	{

		ret_value = system ("curl google.co.in --connect-timeout 12 --max-time 24 &>/dev/null"); // internet connection

		if (ret_value != 0 )
		{
			fprintf(stdout,"Unable to Connect to Internet Retrying..\n");
			sleep(60);  
		}
		else 
		{
			fprintf(stdout,"Internet Found\n");
			return;
		}

	}

	return;
}

int wget_download (char *url,char *Taget_filename) // Mode= Active or Passive, retry_count =retry count to wget
{

	int retry_count_wget = 12;

	char wget_cmd[1024]="";

	int ret=0;

	int i=0;



	memset(wget_cmd,0x00,sizeof(wget_cmd));



	for (  i= 1 ; i <= 20; i++)
	{




		memset(wget_cmd,0x00,sizeof(wget_cmd));
		if ( i%2 == 0 )
		{
			fprintf(stdout,"Active Mode Downloading...\n");
			sprintf(wget_cmd,"/usr/bin/wget -c -T %d %s  -O %s &> /dev/null",retry_count_wget,url,Taget_filename);

		}

		else
		{
			fprintf(stdout,"Passive Mode Downloading...\n");
			sprintf(wget_cmd,"/usr/bin/wget --passive-ftp -c -T %d %s -O %s &> /dev/null",retry_count_wget,url,Taget_filename);

		}

		Wait_for_internet(); //Block until internet 

	puts(wget_cmd);
		ret = system(wget_cmd);

		if (ret == 0)
			break;
		else 
			fprintf(stdout,"Error in server response, retrying %d\n",i);
		
		
		sleep(40);
	}	

	if (ret == 0 )
	{
		fprintf(stdout,"\n%s File Download Success\n",Taget_filename);
		return 0;
	}
	else 
	{
		fprintf(stderr,"\n%s File Download Failed\n",Taget_filename);
		return -1;
	}
}



