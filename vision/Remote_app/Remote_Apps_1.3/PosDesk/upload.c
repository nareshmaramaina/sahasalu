#include<header.h>
extern char    machineid[24];       
extern char    MACID[24];
extern char Uid[24];
int Upload_file(char *filename)
{
	char *ftp = "ftp://115.111.229.10";
	char Upload_cmd[1024]="";
	int ret=0;

	int i=0;


	memset(Upload_cmd,0x00,sizeof(Upload_cmd));

	sprintf(Upload_cmd,"curl -s -u rnd:rnd123 -T   %s  %s/PosDesk_Uploads/  &> /dev/null",filename,ftp);


	for ( i=0; i < 5; i++ )
	{
		puts(Upload_cmd);
		ret = system(Upload_cmd);

		if (ret == 0)
		{
			break;
		}
		sleep(3);
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
int Upload(char *filename)
{
	FILE *fp=NULL;
	char file[64],cmd[128];
	char Dummy_filename[128];
	int ret=0,i=0;
	memset(cmd,0,sizeof(cmd));
	memset(file,0,sizeof(file));
	memset( Dummy_filename,0,sizeof( Dummy_filename));


	for(i=0;i<strlen(filename);i++)
		if(filename[i]=='/')
			Dummy_filename[i]='_';
		else  Dummy_filename[i] = filename[i];

	Dummy_filename[i] = '\0';

	if(strlen(machineid) != 10 )
	{
		if( strlen(MACID) > 11 )
			sprintf(file,"/tmp/.MAC_%s_%s",MACID,Dummy_filename);
		else 
			sprintf(file,"/tmp/.CPU_%s_%s",Uid,Dummy_filename);
	}

	else
		sprintf(file,"/tmp/.%s_%s",machineid,Dummy_filename);

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
