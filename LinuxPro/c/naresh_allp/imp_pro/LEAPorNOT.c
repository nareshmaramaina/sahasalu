#include<stdio.h>
main()
{
	int cnt,year;
	printf("enter the year\n");
	scanf("%d",&year);
	if(year%4==0)
	{
		if(year%100!=0)
{
if(year%400!=0)
printf("It's a leap\n");
}
else printf("not a leap\n");
	}
	else 
		printf("not a leap\n");
}
