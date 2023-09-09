/*
 * =====================================================================================
 *
 *       Filename:  palidrome.c
 *
 *    Description:  iii
 *
 *        Version:  1.0
 *        Created:  Thursday 18 March 2021 11:18:01  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */

#include<stdio.h>
int main()
{
	//char *str="1234  12345654321 Having Two much pressure";
	char *str="1234avingwouchpressure";
	func(str);

	return 0;
}
int func(char *str)
{

	int i,j,k,flag=0,max=1,start=0,size;
	size = strlen(str);

	for(i=0;i<size;i++)
	{

		for(j=i;j<size;j++ )
		{
			flag=1;
			for(k=0;k < ( j-i+1) /2 ; k++)
			{
				if (	str[i+k] != str[j-k] )
					flag =0 ;	
			}
			if ( flag &&   ( j-i+1 ) > max )
			{
				start =i;
				max= ( j-i+1);
			}
		}

	}
	if ( max > 1 )
		printSubStr(str, start, start + max - 1);
	else 
		fprintf(stdout," No Palidrome\n");
	return 0;
}

void printSubStr(char *str, int low, int high)
{
	fprintf(stdout," low %d  high %d\n",low,high); 
	for (int i = low; i <= high; ++i)
		printf("%c",str[i]);
	return;
}
