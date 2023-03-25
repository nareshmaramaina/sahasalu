#include <unistd.h>
#include<stdlib.h> 
#include <signal.h>
#include<stdio.h>
void alaram(int signum)
{
//fflush(stdout);
printf("alaram on\n");
}
int main()
{
printf("enter the password\n");
printf("invoking%d\n",getpid());
signal(14,alaram);
fflush(stdout);
while(1)
{
usleep(1000000);
alarm(1);
}
fflush(stdout);
//fflush(stdout);




}
