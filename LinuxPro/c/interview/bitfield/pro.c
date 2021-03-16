/*
 * =====================================================================================
 *
 *       Filename:  pro.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 12 March 2021 11:57:01  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */

#include <stdio.h> 

// Space optimized representation of the date 
struct date { 
	// d has value between 1 and 31, so 5 bits 
	// are sufficient 
	unsigned int d : 5; 
	// m has value between 1 and 12, so 4 bits 
	// are sufficient 
	int m : 4; 

	unsigned short int y; 
}; 

int main() 
{ 
	printf("Size of date is %lu bytes\n", sizeof(struct date)); 
	struct date dt = { 35, 49, 131073}; 
	printf("Date is %d/%d/%d\n", dt.d, dt.m, dt.y); 
	return 0; 
}

