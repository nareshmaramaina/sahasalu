/*
 * =====================================================================================
 *
 *       Filename:  output1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 12 March 2021 12:41:44  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */


#include <stdio.h> 
struct test { 
	unsigned int x; 
	long int y : 32; 
	unsigned int z; 
}; 
int main() 
{ 
	struct test t; 
	unsigned int* ptr1 = &t.x; 
	unsigned int* ptr2 = &t.z; 
	printf("%d %d", ( char * )ptr2 - ( char *) ptr1,sizeof( struct test) ); 
	return 0; 
} 

