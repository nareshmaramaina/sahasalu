#include<stdio.h>
int main()
{

printf("%d\n",Fibonacci(100));
return 0;
}
int Fibonacci(int numbers)
{
int a=0,b=1,c;
printf(" %d %d ", a,b);
for(int num=2;num<=numbers;num++)
{
c = a+b;
a=b;
b=c;
printf("%d ",c);
}



return c;
}
