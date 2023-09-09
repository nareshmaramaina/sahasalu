#include<stdio.h>
int main()
{
int i,from,to,cnt=0;
printf("enter the from year\n");
scanf("%d",&from);
printf("enter the from year\n");
scanf("%d",&to);
for(i=from;i<=to;i++)
{
if(i%4==0)
cnt++;
}
printf("leap years %d\n",cnt);
}
