/*
 * =====================================================================================
 *
 *       Filename:  conversion.c
 *
 *    Description:  ii
 *
 *        Version:  1.0
 *        Created:  Friday 12 March 2021 03:12:25  IST
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
	int arr[3][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
	int num;
	printf(" %d \n",sizeof(arr));
	printf("num = %d %d  \n", arr[2][3],  *(*(arr+2) + 2 ) );
	func(arr+2);
	return EXIT_SUCCESS;
}		

/* ----------  end of function main  ---------- */


int func(int ***arr)
{
	int i=0;
	printf(" %d \n",sizeof(arr));
	for ( i =0 ; i< 4;i++)
	{
		printf(" %d %d \n",i, arr[0][i]);
	}
	return 0;
}
