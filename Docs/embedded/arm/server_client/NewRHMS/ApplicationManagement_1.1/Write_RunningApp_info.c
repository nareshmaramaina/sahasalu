#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Write_RunningApp_info(char *ApplicationType,char *ApplicationName,char *Version);
int main()
{
	Write_RunningApp_info("PDS","APPDS","1.3.2"); // Example APP type, App name, version
	return 0;
}
void Write_RunningApp_info(char *ApplicationType,char *ApplicationName,char *Version)
{
	char App_info_file[560];
	FILE *fp=NULL;
	memset(App_info_file,0,sizeof(App_info_file));

	sprintf(App_info_file,"mkdir -p /etc/vision/RHMS/RunningApps/%s/%s",ApplicationType,ApplicationName);
	system(App_info_file);
	memset(App_info_file,0,sizeof(App_info_file));

	sprintf(App_info_file,"/etc/vision/RHMS/RunningApps/%s/%s/app.info",ApplicationType,ApplicationName);


	fp = fopen(App_info_file,"w");
	if ( fp == NULL)
	{
		fprintf(stderr,"%s file not found \n",App_info_file);
		return;
	}


	fprintf(fp,"ApplicationType:%s\nApplicationName:%s\nVersion:%s\n",ApplicationType,ApplicationName,Version);
	fprintf(stdout,"App info file = %s\nApplicationType:%s\nApplicationName:%s\nVersion:%s\n",App_info_file,ApplicationType,ApplicationName,Version);

	fclose(fp);

	return;
}
