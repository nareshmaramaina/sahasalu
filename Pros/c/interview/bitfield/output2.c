/*
 * =====================================================================================
 *
 *       Filename:  output2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 12 March 2021 12:53:49  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */

union test { 
	unsigned int x : 3; 
	unsigned int y : 3; 
	int z; 
}; 

int main() 
{ 
	union test t; 
	t.x = 5; 
	t.y = 4; 
	t.z = 1; 
	printf("t.x = %d, t.y = %d, t.z = %d", 
		t.x, t.y, t.z); 
	return 0; 
} 

