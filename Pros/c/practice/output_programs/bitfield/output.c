/*
 * =====================================================================================
 *
 *       Filename:  output.c
 *
 *    Description:  kkk
 *
 *        Version:  1.0
 *        Created:  Friday 12 March 2021 12:40:31  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */

/* width Excedded Error */
#include <stdio.h> 
struct test { 
    unsigned int x; 
    unsigned int y : 33; 
    unsigned int z; 
}; 
int main() 
{ 
    printf("%lu", sizeof(struct test)); 
    return 0; 
} 

