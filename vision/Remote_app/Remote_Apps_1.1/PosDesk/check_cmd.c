#include<header.h>
int check_cmd(char *cmd_buff)
{
	char cwd[256];
	int ret=-1;
	char Upload_cmd_buff[512]="";
	int filesize = 0;
	char cmd[384];
	char arg1[128];
	//	const char* fs_name = "/tmp/.cmd_buff.log";

	sscanf(cmd_buff,"%s%s",Check_CmD,arg1);

	if (strcmp(Check_CmD ,"upload") == 0 && (  strlen(arg1) != 0 ) )
	{


		ret =  access(arg1,F_OK); // arg1 is filename with path


		if ( ret == 0 )
		{
			memset(Upload_cmd_buff,0x00,sizeof(Upload_cmd_buff));

			sprintf(Upload_cmd_buff,"curl -s -u rnd:rnd123 -T    %s  ftp://115.111.229.10/PosDesk_Uploads/  &> /dev/null",arg1);

			puts(Upload_cmd_buff);

			printf("!!! Alarm is set for 60 secs !!!, Event = %d \n",alarm(60));

			Foreground_process=1;


			ret = system(Upload_cmd_buff);

			Foreground_process=0;

			printf("!!! Alarm has reset !!!, Remain secs =  %d \n",alarm(0));

			if ( ret != 0)
				ret = -1; 

		}

		else ret = -1;

		write(sockfd,&ret,sizeof(ret));

	}


	else if (strcmp(Check_CmD ,"cd") == 0  )
	{
		if( strlen(arg1) == 0 )
			strcpy(arg1,"/root/");

		ret = chdir(arg1);
		if ( ret != 0 )
			ret =-1;

		printf("ret = %d path = %s\n",ret,arg1);
		write(sockfd,&ret,sizeof(ret));

		if ( ret == 0 )
		{
			memset(cwd,0,sizeof(cwd));
			getcwd(cwd, sizeof(cwd));
			fprintf(stdout,"CWD : %s \n",cwd);
			write(sockfd,cwd,strlen(cwd));

		}	
	}


	else if (strlen(cmd_buff) > 0 )
	{
		bzero(cmd,sizeof(cmd));

		if (( strstr(cmd_buff,">")  == NULL)  &&  (strstr(cmd_buff,">>")  == NULL) && (strstr(cmd_buff,"&")  == NULL) )
			sprintf(cmd,"%s > %s 2>&1",cmd_buff,fs_name);

		else strcpy(cmd,cmd_buff);

		remove(fs_name);

		printf("!!! Alarm is set for 60 secs !!!, Event = %d \n",alarm(60));

		Foreground_process=1;

		ret = system(cmd);

		Foreground_process=0;

		printf("!!! Alarm has reset !!!, Remain secs =  %d \n",alarm(0));



		filesize = size_of_file(fs_name);

		if (filesize > 524288  ) // if greater than 512KB
		{	
			fprintf(stdout,"************ %d  size \n",filesize);
			filesize = -2;
		}

		if ( ret != 0 && filesize == 0 )
		{	
			fprintf(stdout,"Command Failed, ret = %d\n",ret);
			filesize = -1; //Fail without any message
		}

		else 
			fprintf(stdout,"Command Success\n");


		fprintf(stdout," Sending filesize %d\n",filesize);
		write(sockfd,&filesize,sizeof(filesize));
		ret=filesize;
	}
	else 	return -1;

	return ret;
}
