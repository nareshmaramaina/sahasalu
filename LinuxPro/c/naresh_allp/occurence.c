#include<string.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	char str[100]="";
	char *ptr=NULL;
	int in,out,hour,mins,occu,i,flag=0;
	int total_in_hr=0,total_in_sec=0;
	int total_out_hr=0,total_out_sec=0;
	printf("Paste your In time&& out time data (hr/min) after enter ( e or q or exit)\n");

	while(fgets(str,100,stdin))
	{
	if((strcmp(str,"e\n")==0)||strcmp(str,"q\n")==0||strcmp(str,"exit\n")==0)
			break;
		if(strstr(str,":")==NULL)
		continue;
	do{
		if(strlen(str)<=2)
		break;
	sscanf(str,"%2d:%2d",&hour,&mins);
			if(mins>=60)
			{
			printf("&&& Alert: Wrong secs entered\n");
			break;
	}
			if(hour>=8&&hour<13)
			{
				if(hour>=11)
					hour=9;
				total_in_hr += (hour-9);
				total_in_sec += mins;
			}
			else if(hour>=18&&hour<=23) 
			{
				if(hour==18&&mins<30)
					mins=0;
				total_out_hr+=(hour-18);
				total_out_sec+=mins;
			}
			if((ptr=strstr(str," "))) flag=1;
			else if(ptr=strstr(str,"	"))flag=1;
			if(flag)
			{
				for(i=0;ptr[i]=='\t'||ptr[i]==' ';i++);
				strcpy(str,ptr+i);
				flag=0;
			}
			else break;

	}while(1);
	memset(str,0,100);
	}
	system("clear");
	printf("\n\n*************************************************************\n");
	printf("Total IN-TIME in secs = %d",in=total_in_sec+(total_in_hr*60));
	printf("\tTotal OUT-TIME in secs = %d\n",out=total_out_sec+(total_out_hr*60));
	printf("Total IN-TIME hrs = %d:%d",total_in_hr+(total_in_sec/60), total_in_sec%60);
	printf("\tTotal OUT-TIME hrs = %d:%d\n",total_out_hr+(total_out_sec/60), total_out_sec%60);
	occu=in-out;
	if(occu<0)
		printf("Congralations You have more time, in secs =%d",-(occu));
	else
		printf("Need To Cover Occurence in secs	= %d",occu);
	printf("\n\n*************************************************************\n");
	return 0;
}
