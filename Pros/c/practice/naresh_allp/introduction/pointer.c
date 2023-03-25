#include<stdio.h>
#include<stdlib.h>
int main()
{
int **ptr,*ptr1,*ptr2;
ptr1=malloc(4);
ptr1=10;
ptr=ptr1;
printf("%d\n",**ptr);
}
