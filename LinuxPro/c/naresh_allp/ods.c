#include<stdio.h>
#include<stdio.h>
int main()
{
char buff[20]="";
FILE *fp=NULL;
fp=fopen("/home/naresh/Desktop/sample_file.xls","r");
while(fgets(buff,20,fp))
puts(buff);
}
