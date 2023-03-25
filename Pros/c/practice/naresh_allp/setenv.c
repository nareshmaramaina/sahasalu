#include<stdio.h>
#include<stdlib.h>
int main()
{
char *name="NAME";
       setenv(name,"11203040",0);
putenv(name);
return 0;
}
