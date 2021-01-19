#include<stdio.h>
#include<stdlib.h>
int main()
{
int i, x=100;
srand(getpid());
for(i=0;i<100;i++)
printf("%4d",rand()%1000);
}
