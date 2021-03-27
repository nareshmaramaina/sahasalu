/*
 * =====================================================================================
 *
 *       Filename:  naresh.c
 *
 *    Description:  ii
 *
 *        Version:  1.0
 *        Created:  Monday 22 March 2021 09:51:34  IST
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
	int num=10;
	static int naresh;
	naresh = num;
	printf("num = %d \n",num);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
