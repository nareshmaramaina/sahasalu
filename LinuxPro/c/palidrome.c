#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	if ( palidrome( 121) == 0 )
		printf(" palidorme \n");

	return 0;
}
int palidrome( int num)
{
	int actual=num,pali=0;
	int remain;
	while( num )
	{
		remain= num%10;
		num=num/10;
		pali=(pali * 10 ) + remain;
	}

	if ( pali == actual )
	return 0;
	else return 1;
}
