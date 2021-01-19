#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{


printf("%d", my_time());
}
int my_time(void)
{
struct tm *tmstmp;
time_t timeval;
time(&timeval);
char date_str[30]="";
tmstmp= localtime(&timeval);

        sprintf(date_str,"/%02d/%02d/%02d,%02d:%02d:%02d\n",tmstmp->tm_year+1900,tmstmp->tm_mday,tmstmp->tm_mon+1,tmstmp->tm_hour,tmstmp->tm_min,tmstmp->tm_sec);

printf("The date is: %s",date_str);
return 0;
}
