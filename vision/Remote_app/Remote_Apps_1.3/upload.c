
#include<header.h>

char macid[24]="7e:00:99:00:33:ef";
int Upload_file(char *filename)
{
	char *ftp = "ftp://115.111.229.10";
	char Upload_cmd[1024]="";
	int ret=0;

	int i=0;

	int ret_value=0;

	memset(Upload_cmd,0x00,sizeof(Upload_cmd));

	sprintf(Upload_cmd,"curl -s -u rnd:rnd123 -T   %s  %s/PosDesk_Uploads/%s/  &> /dev/null",filename,ftp,Notifier.topic);

	puts(Upload_cmd);

	for ( i=0; i < 20; i++ )
	{
		ret_value = system ("curl google.co.in --connect-timeout 12 --max-time 24 &>/dev/null"); // internet connection

		if (ret_value != 0 )
		{
			fprintf(stdout,"Unable to Connect to Internet Retrying..\n");
			sleep(60);  
			i--;
			continue;
		}
		else 
		{
			printf(" Uploading ..... %s\n",filename);

			ret = system(Upload_cmd);

			if (ret == 0)
			{
				break;
			}
		}
		sleep(40);
	}	

	if (ret == 0 )
	{
		fprintf(stdout,"\n%s File Upload Success\n",filename);
		return 0;
	}
	else 
	{
		fprintf(stderr,"\n%s File Upload Failed\n",filename);
		return -1;
	}
}
int main ()
{

	Upload("/root/a.out");
	return 0;
}
int Upload(char *filename)
{
	FILE *fp=NULL;
	char machineid[20]="";
	char file[64],cmd[128];
	char Dummy_filename[128];
	int ret=0,i=0;
	memset(machineid,0,sizeof(machineid));
	memset(cmd,0,sizeof(cmd));
	memset(file,0,sizeof(file));
	memset( Dummy_filename,0,sizeof( Dummy_filename));
	if (strcmp(filename,"REPORT") == 0 )
	{
		memset(filename,0,sizeof(filename));
		strcpy(filename,"/var/log/.mosquitto/All_Modes_Report");	
	}
	ret = system("fw_printenv machineid  | cut -c11-20 > /tmp/.machineid");

	if ( ret == 0 )
	{
		fp=fopen("/tmp/.machineid","r");

		if(fp == NULL)
		{
			printf("opening error /tmp/.machineid\n");
			return -1;
		}

		fscanf(fp,"%s",machineid);

		fclose(fp);

		remove("/tmp/.machineid");
	}


	for(i=0;i<strlen(filename);i++)
		if(filename[i]=='/')
			Dummy_filename[i]='_';
		else  Dummy_filename[i] = filename[i];

	Dummy_filename[i] = '\0';

	if(strlen(machineid) == 0 )
		sprintf(file,"/tmp/.%c%c%c%c%c%c%c%c%c%c%c%c%s",macid[0],macid[1],macid[3],macid[4],macid[6],macid[7],macid[9],macid[10],macid[12],macid[13],macid[15],macid[16],Dummy_filename);

	else
		sprintf(file,"/tmp/.%s%s",machineid,Dummy_filename);

	ret = access(filename,F_OK); 
	if ( ret != 0)
	{
		fp  = fopen(file,"w");

		if(fp == NULL)
		{
			printf("opening error %s\n",file);
			return -1;
		}

		fprintf(fp,"%s file not found\n",filename);

		fclose(fp);


	}

	else 
		sprintf(cmd,"cp %s %s",filename,file);	
	printf("Upload Copy Command = %s\n",cmd);
	system(cmd);

	return Upload_file(file);

}
