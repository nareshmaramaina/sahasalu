#include"../include/header.h"
void get_date(int *day,int *month,int *year)
{
	struct tm *intim;
	struct tm my_tm;
	struct timeval tv;
	intim = &my_tm;

	memset(intim,0,sizeof(struct tm));

	gettimeofday (&tv,NULL);

	intim = localtime (&tv.tv_sec) ;

	*day=intim->tm_mday;
	*month=intim->tm_mon+1;
	*year=intim->tm_year+1900;


	return;
}

