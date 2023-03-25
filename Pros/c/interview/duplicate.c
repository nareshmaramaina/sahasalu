/*
 * =====================================================================================
 *
 *       Filename:  duplicate.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 16 April 2021 12:21:26  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */


#include<stdlib.h>
#include<stdio.h>
int main ( int argc, char *argv[] )
{
	int a[]={9,20,9,1,2,3,3,3,21,34,5,5,5},tmp;
	int i,j,size=sizeof(a)/sizeof(*a),flag;


	// If sorted Then Use Below 
	
	for( i =0; i< size; tmp=a[i++])
		if (  i==0  ||  tmp != a[i]  )
			printf(" %d \n", a[i] );
	// If not sorted Then Use Below 
	printf(" Un sorted Also Works \n");
	for( i =0; i< size; i++ )
	{
		for ( flag = 1,j =i+1 ; j<size;j++ )
		{
			if  ( a[i] == a[j] )
			{
				flag=0;
				break;
			}
		} 
		if ( flag )
			printf(" %d \n", a[i] );
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
