#include<stdio.h>
#include<stdlib.h>
int main()
{
char buff[80]="";
FILE *fp=NULL;
fp=popen("ls","r");
while(fgets(buff,80,fp))
puts(buff);
pclose(fp);
}
