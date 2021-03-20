#include <header.h>
/*static int diff_bw_two_dates(int firstDate, int firstMonth, int firstYear, int secondDate, int secondMonth, int secondYear)
{
	int FirstNoOfDays=0;
	int SecondNoOfDays=0;

	firstMonth = (firstMonth + 9) % 12;
	firstYear = firstYear - firstMonth / 10;
	FirstNoOfDays = 365 * firstYear + firstYear/4 - firstYear/100 + firstYear/400 + (firstMonth * 306 + 5) /10 + ( firstDate - 1 );

	secondMonth = (secondMonth + 9) % 12;
	secondYear = secondYear - secondMonth / 10;
	SecondNoOfDays = 365 * secondYear + secondYear/4 - secondYear/100 + secondYear/400 + (secondMonth * 306 + 5) /10 + ( secondDate - 1 );

	return FirstNoOfDays - SecondNoOfDays;  
}
int  Check_Expire_Date(void)
{
	int day=0,month=0,year=0,hrs=0,mins=0,secs=0;

	int expireDay=26,expireMonth=04,expireYear=2019;

	get_date(&day,&month,&year,&hrs,&mins,&secs);

	return diff_bw_two_dates(day, month, year,expireDay ,expireMonth ,expireYear );
	
}*/
void get_date(int *day,int *month,int *year,int *hrs,int *mins,int *secs)
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
	*hrs=intim->tm_hour;
	*mins=intim->tm_min;
	*secs=intim->tm_sec;

	return;
}

