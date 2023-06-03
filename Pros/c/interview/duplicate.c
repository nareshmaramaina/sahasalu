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
	int a[]={9,20,9,1,2,3,3,3,21,34,5,5,3,34},tmp;
	int i,j,size=sizeof(a)/sizeof(*a),flag;

	printf("\nGiven Elements:\t");
	for ( i=0; i< size; i++)
		printf("%d,",a[i]);
	printf("\nUnsorted Removed Duplicates:\t");
	for(i=0;i<size;i++) {
		for ( j = i+1; j < size ; j++ ) {
			if( a[i] == a[j] )
				break;
		}
		if ( j >= size )
			printf("%d,",a[i]);
	}

	printf("\nSorted Array:\t");
	for( i=0; i< size; i++) {
		for( j=i+1;j<size;j++) {
			if ( a[i] > a[j] ) {
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}

	}
	for ( i=0; i< size; i++)
		printf("%d,",a[i]);
	printf("\nsorted Removed Duplicates:\t");
	for ( i=0; i< size-1; i++) {
		if ( a[i] != a[i+1] )
		printf("%d,",a[i]);
	}
		printf("%d,",a[i]);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
