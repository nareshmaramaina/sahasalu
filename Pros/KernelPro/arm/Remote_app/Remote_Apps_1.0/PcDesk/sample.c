#include<stdio.h>
#include<string.h>
int main()
{
char cmd[20]="Hi LLL LLL";
char rmd[50];

char str[20]="jithu";
//memcpy(str+2,str,strlen(str)+1);
sprintf(rmd,"rmold%s",cmd+2);
strcpy(cmd,rmd);
puts(cmd);
return 0;
}
