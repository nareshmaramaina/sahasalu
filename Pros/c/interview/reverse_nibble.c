/*
 * =====================================================================================
 *
 *       Filename:  static.c
 *
 *    Description:  ii
 *
 *        Version:  1.0
 *        Created:  Saturday 20 March 2021 10:04:56  IST
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
void nibblereverse ( int num)
{
	int i=0;
	int output, Final=0;
	for(i=0;i<8;i++)
	{
		output =  ( num >>  ( i * 4 ) ) & 0xf; 
		output =	(( output & 0x8 ) >> 3) | (( output & 0x4 ) >> 1)  | ( ( output & 0x2 ) << 1) | ( ( output & 0x1 ) << 3) ;

		
		Final = Final | ( output  << ( i*4 ) ) ;
	}
	printBits(Final);
	return;
}
int main ( int argc, char *argv[] )
{
	register int num=4234;
	printBits(num);
	nibblereverse(num);
	return EXIT_SUCCESS;
}	

/* ----------  end of function main  ---------- */
int Bits(int num)
{
        int i=0;

        for(i= 4 ; i >= 0 ; i-- )
                printf("%d", ( num >> i ) & 1 );
        putchar('\n');
        return 0;
}

int printBits(int num)
{
	int i=0;

	for(i= 31 ; i >= 0 ; i-- )
		printf("%d", ( num >> i ) & 1 );
	putchar('\n');
	return 0;
}
//		printf(" Final ");
//		printBits( (( output & 0x8 ) >> 3) | (( output & 0x4 ) >> 1)  | ( ( output & 0x2 ) << 1) | ( ( output & 0x1 ) << 3) );
//		printf(" Final %d \n",(( output & 0x8 ) >> 3) | (( output & 0x4 ) >> 1)  | ( ( output & 0x2 ) << 1) | ( ( output & 0x1 ) << 1));
/*	printf("%d\n",   ( output & 0x8 ) >> 3);
	printf("%d\n",   ( output & 0x4 ) >> 1);
	printf("%d\n",   ( output & 0x2 ) << 1);
	printf("%d\n",   ( output & 0x1 ) << 1);
	printf("%d\n",   ( output >> 1) & 4 ); 
	printf("%d\n",   ( output << 3) & 2 );
	printf("%d\n",   ( output << 1)& 1 ) ; */
