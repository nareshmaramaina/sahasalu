#include<stdio.h>
char *fun()
{
char str[]="naresh";
return str;
}
int main()
{
char *str;
str=fun();
puts(str);
}
