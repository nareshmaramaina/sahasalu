#include<math.h>
#include<stdio.h>
int main()
{
 int num,i,j;
char str[10];
printf("enter the string\n");
scanf("%s",str);
for(i=strlen(str)-1;i<=0;i--)
{
if(str[i]=='k')num=10;
else if(str[i]=='m')num=20;
else if(str[i]=='g')num=30;
else if(str[i]=='b')num=8;
else  i=str[i]-48;
}
//printf("enter the number\n");
//scanf("%d",&i);
printf("%d\n",j=pow(2,num));
}
