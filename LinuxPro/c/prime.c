#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
for (int i  =0; i<100;i++)
{
	if ( prime(i) == 0 )
	printf("%d,",i);	
}


return 0;
}
int prime(int num)
{
for(int i=2; i<num; i++)
{
if(num%i == 0 )
return -1;
}
return 0;
}

