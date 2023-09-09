/*
 * =====================================================================================
 *
 *       Filename:  google.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Saturday 06 March 2021 03:44:05  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */

#include <stdio.h>

// returns true if X and Y are same
int compare(const char *X,const  char *Y)
{
	while (*X && *Y)
	{
		if (*X != *Y)
			return 0;

		X++;
		Y++;
	}
	if ( ! *Y )
		return 1; 
	return 0;
}

// Function to implement My_Strstr() function
char* My_Strstr(const char* X, const char* Y)
{
	while (*X != '\0')
	{
		if ((*X == *Y) && compare(X, Y))
			return X;
		X++;
	}

	return NULL;
}

// Implement My_Strstr function in C
int main()
{
	char X[] = "Techie Delight - Coding made easy";
	char Y[] = "Coding";
	char *str;
	if (  ( str = My_Strstr(X, "-") )== NULL )
		fprintf(stdout," Null Found \n");

	else printf( " %s \n" ,str);
	return 0;
}
