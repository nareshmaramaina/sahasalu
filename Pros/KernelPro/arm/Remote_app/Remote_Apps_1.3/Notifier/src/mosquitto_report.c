#include <header.h>

void mosquitto_report(char *mode,char *msg,char *cmd_status)
{
	FILE *fp;

	char *log_file="/var/log/.mosquitto/All_Modes_Report";

	int day=0,month=0,year=0,hrs=0,mins=0,secs=0;

	get_date(&day,&month,&year,&hrs,&mins,&secs);

	fp = fopen(log_file,"a");
	if( fp == NULL)
	{
		fprintf(stderr," %s open failed\n",log_file);
		return;
	}
	fprintf(fp,"[ %02d/%02d/%04d-%02d:%02d:%02d ]\tMode:%s\tMessage:%s\tStatus:%s\n",day,month,year,hrs,mins,secs,mode,msg,cmd_status);

	fprintf(stdout,"[ %02d/%02d/%04d-%02d:%02d:%02d ]\tMode:%s\tMessage:%s\tStatus:%s\n",day,month,year,hrs,mins,secs,mode,msg,cmd_status);

	fclose(fp);

}

