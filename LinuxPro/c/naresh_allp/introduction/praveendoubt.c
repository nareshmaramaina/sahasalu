#include<stdio.h>
int main()
{
volatile int i=1,j;
j=((i) + (++i) + (i++) + (i) + (++i));
printf("%d\n",j);
//printf("%d %d %d %d %d \n",i,++i,i++,i,++i);
}
