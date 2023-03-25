#include<stdio.h>
int main()
{
union tag
{
int num;
char name[30];
}man;
printf("%d %d\n",man.num,man.name);
}
