#include<header.h>
void get_time(char *date,char *time) 
{
	struct tm *intim;
	struct tm my_tm;
	struct timeval tv;

	intim = &my_tm;

	memset(intim,0,sizeof(struct tm));

	gettimeofday (&tv,NULL);

	intim = localtime (&tv.tv_sec) ;

	sprintf(date,"%02d-%02d-%04d",intim->tm_mday,intim->tm_mon+1,intim->tm_year+1900);
	sprintf(time,"%02d:%02d:%02d",intim->tm_hour,intim->tm_min,intim->tm_sec);

	return ;
}
