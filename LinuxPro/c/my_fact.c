#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
my_fact(4);
printf(" ");

return 0;
}
int my_fact(int num)
{
	int val=1;
for ( ;num>1;num--)
{
val=val*num;
printf("%d\n",val);
}
return 0;
}
