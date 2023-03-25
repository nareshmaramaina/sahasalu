#include<stdio.h>
int main()
{
printf("%d\n",fibno(9));
return 0;
}
int fibno(int num)
{
int ret;
if( num == 1 || num == 2)
	return 1;

 ret = fibno(num-1)+fibno(num-2);

 printf("%d ",ret);

 return ret;
}
