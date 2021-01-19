#include<stdio.h>
int a(int (*callback)(void))
{
printf("inside parent function\n");
//test();
//callback();
printf("again call back\n");
}
callback();
int test()
{
printf("inside callback function\n");
}
int main()
{
a(&main);
printf("main gotta end\n");
return 0;
}
