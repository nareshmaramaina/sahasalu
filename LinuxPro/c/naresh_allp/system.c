#include<stdio.h>

int main(int argc,char *argv[])
{
char buff[80]="";
int ret;
sprintf(buff,"rm  %s %s ",argv[1],argv[2]);
ret= system(buff);
return 0;
}
