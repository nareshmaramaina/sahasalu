    #include <unistd.h>
#include<stdlib.h> 
#include <signal.h>
#include<stdio.h>
void wakeup(int signum)
{
printf("it is coming and get exiting\n");
raise(SIGKILL);
}
int main()
{
char buffer[81];
int ret;
signal(SIGALRM,wakeup);
printf("enter the password int 3 seconds\n");
alarm(5);
while(1);
//ret=read(0,buffer,81);
//alarm(0);
//if(ret!=-1)
//{
//printf("invoked %s\n",buffer);
//}
}
