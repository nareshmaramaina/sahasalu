#include<stdio.h>
int static fun()
{
int i=0;
printf("%d\n",++i);
return i;
}
int main()
{
int i;
i=fun();
printf("%d\n",i);
i=fun();
printf("%d\n",i);
i=fun();
printf("%d\n",i);
i=fun();
printf("%d\n",i);
i=fun();
printf("%d\n",i);
}
