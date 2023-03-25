#include<stdio.h>
   #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void main()
{
	int fd;
int a=9,n,a1,sum=0,b,sum1=0;
int cnt=0;
char str[50],*p;
char buff[10];
input:while(fgets(str,50,stdin)!=NULL)
{
if(((str[0]>=65)&&(str[0]<=90))||((str[0]>=97)&&(str[0]<=122)))
continue;
if((p=strstr(str,":"))!=NULL)
{
	n=strlen(str)-strlen(p);
	strncpy(buff,str,n);
	a1=atoi(buff);
	a1-=a;
	a1*=60;
	p+=1;
	strcpy(str,p);
	if((p=strstr(str,":"))!=NULL)
	{
		n=strlen(str)-strlen(p);
		strncpy(buff,str,n);
		b=atoi(buff);
if(cnt==1)
sum1+=a1+b;
else
sum+=a1+b;
	}
}
}
cnt++;
if(cnt==1)
{
printf("copy ur out time occurence:\n");
a=6;
goto input;
}
printf("in occurence sum:%d\n",sum);
printf("out occurence sum:%d\n",sum1);
sum-=sum1;
if(sum>0)
printf("total u have to stay %d minutes:\n",sum);
else
printf("good ur maintaind good occurency\n");
//while(1);
}
