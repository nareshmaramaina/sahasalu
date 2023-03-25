#include <signal.h>
#include<stdio.h>
void naresh(int signum)
{
fflush(stdout);
//getchar();
printf(" naresh");
}
int main()
{
printf("enter the number\n");
signal(2,naresh);
while(1);

}
