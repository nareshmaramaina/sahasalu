#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
const int i;
int *p;
printf(" %d \n",i);
p=&i;
*p=10;
printf(" %d \n",i);
return 0;
}
