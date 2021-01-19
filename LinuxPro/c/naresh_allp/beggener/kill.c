#include <sys/types.h>
       #include <signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
printf("it is at first\n");
getpid();
kill(getpid(),9);
printf("it is at lastt\n");

}
