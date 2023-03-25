#include<stdio.h>
int main()
{
	int a = 18;
	int b = 98;
	

	// 				 64 32 16  8 4 2 1
	//  				  0  0  1  0 0 1 0
	//  				  1  1  0  0 0 1 0 
	//  a^=b , a = a  ^ b   a = 	  1  1  1  0 0 0 0   a = a and b VAlues  B = sum +b = a  a = sum + b = b 
	//  			b= 	  1  1  0  0 0 1 0 
	//  b^=a , b = b  ^ a	 b=       0  0  1  0 0 1 0   = 18 
	//  			 a =      1  1  1  0 0 0 0 
	//  a^=b , a = a  ^ b    a =      1  1  0  0 0 1 0 = 98 			 
	printf("a =  %d, b =  %d\n",a,b);
	a^=b;
	b^=a;
	a^=b;
	printf("a =  %d, b =  %d\n",a,b);

	
	return 0;
}
