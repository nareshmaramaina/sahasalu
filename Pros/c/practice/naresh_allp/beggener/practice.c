#include<stdio.h>
#include<time.h>
int main()
{
static int hour,sec,n,min,j;
time_t times;
long unsigned int k;
times=time(0);
printf("actual time %lu\n",times);
//printf("enter how many days to back\n");
//scanf("%d",&n);
k=2017*3600*24;
printf("entered days back %d      %lu\n",n,k=times-k);
j=k/3600;
printf("%d\n",j);
}
