/*
 * =====================================================================================
 *
 *       Filename:  anagram.c
 *
 *    Description:  angram
 *
 *        Version:  1.0
 *        Created:  Friday 26 February 2021 04:01:26  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<stdlib.h>

int myatoi(char *str)
{
	int i,tmp=0;
	for(i=0;str[i];i++)
	{
		if ( str[i] >= '0' && str[i] <= '9' )
			tmp=tmp*10+ str[i]-'0';
		else break;
	}	
	return tmp;
}

char *myitoa(int num)
{
	// 30 60  97  = a 
	char *string=NULL,tmp;
	int k=0;
	string = malloc(sizeof(num)*8);
	if ( string == NULL )
		return NULL;
	int i=0,j,size= (sizeof(num)*8 ) -1,val=num;

	if ( num < 0 )
	{
		num= num *  -1;
		string[0]='-';
		k=1;
	}

	for( i =k; num;i++)
	{
		string[i] = (num % 10 ) + '0';
		num = num/10;
	}
	
	size = strlen(string)+k;
	printf( "szied = %d %s\n",size,string);
	for(i=k;i<size/2;i++)	
	{
		tmp = string[i];
		string[i]=string[size-i-1];
		string[size-i-1]=tmp;
		printf(" Itereations \n");
	}	
	return string;
}
int main ( int argc, char *argv[] )
{
	if ( argc < 2 )
		return -1;
	int num=atoi(argv[1]);
	printf( " %s \n",myitoa(num) );
	//	palidrome(myatoi(argv[1]));

	return EXIT_SUCCESS;
}	

void palidrome(int num)
{
	int tmp = num;
	int val=0;
	while(tmp )
	{
		val = val * 10 +   ( tmp%10);
		tmp = tmp/10;

	}	
	if ( val == num )
		fprintf(stdout," Paligrame\n");
	else 
		fprintf(stdout," Paligrame kadhu\n");
	printf(" num = %d  result = %d \n", num,val);
	return;
}			/* ----------  end of function main  ---------- */
	void
anagram ( int num )
{
	return ;
}		/* -----  end of function anagram  ----- */
