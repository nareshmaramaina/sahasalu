#include<string.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{

FILE *fp=NULL;
char cmd[68]="";
int some;
char buff[128]="";
//system("fw_printenv | grep machineid | cut -c11-21 > machineid");
fp=fopen("machineid","r");
fgets(buff,128,fp);
if(buff[strlen(buff)-1]=='\n')
buff[strlen(buff)-1]=='\0';
sprintf(cmd,"temp1=%s",buff);
puts(buff);
puts(cmd);
if(system(cmd)!=0)
printf("error1\n");
system("echo $temp1");
//system("printenv");
char *kaya="temp1";
char *str;
str=getenv("temp1");
setenv(kaya,"temp1",0);
if(putenv(kaya)!=0)
printf("error\n");
return 0;
}
