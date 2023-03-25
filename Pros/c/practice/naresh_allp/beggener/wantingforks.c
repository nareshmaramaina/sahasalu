#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
int n,i,j;
printf("enter the wanted forks\n");
scanf("%d",&n);
for(i=1;i<=n;i++)
{
if(fork()==0)
{
printf("fork ppid%d\n",getppid());
exit(1);
}
else 
{
sleep(1);
printf("parent ppid%d\n",getppid());
}
fflush(stdout);
}
sleep(1);
}
