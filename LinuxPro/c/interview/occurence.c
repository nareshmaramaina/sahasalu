/*
 * =====================================================================================
 *
 *       Filename:  occurence.c
 *
 *    Description:  ii
 *
 *        Version:  1.0
 *        Created:  Wednesday 17 March 2021 12:11:03  IST
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
	int num;
	char *str="AAAABBBBCCCCDDDD";
		printf("num = %d \n",num);
	func(str);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

void func(char *str)
{
	int i,j,count,size,k=0;
	char *output;
	size = strlen(str);
	output= malloc(size);
	

	for(i=0;i< size ;i++)
	{
		count=0;
		for( j=0;j<i;j++)
		{
			if (str[i] == output[j]  )
				count=1;

		}
		if (count == 0)
		{

			output[k++] = str[i];
		}

	}
	puts(output);
	return;
}
