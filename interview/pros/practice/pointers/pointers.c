#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
int *p;
p=malloc(sizeof(int));
p[0]=9;
printf("%d\n",p[0]);

return 0;
}
