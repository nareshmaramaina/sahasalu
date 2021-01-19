
#include<stdio.h>
int *fun()
{
int *ptr,b=90;
ptr=&b;
printf("ptr=%d\t%d\n",ptr,&b);
return ptr;
}
int main()
{
int *a=NULL;
printf(" %d\n",a);
a=fun();
printf(" %d\n",a);
}
