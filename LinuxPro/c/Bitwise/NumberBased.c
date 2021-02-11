#include<stdio.h>
int main()
{
	// Power of 2 
	int num;
	while(1)
	{
		printf("Enter A number \n");
		scanf("%d",&num);
		//		PowerOf2(num);
	//	PowerOf2_Logic2(num);
	//odd_or_even(num);
	//		CountNumberOfSetBits(num);
	}
}
unsigned int reverseBits(unsigned int num)
{
	unsigned int rev =0 ,pos = (sizeof(int) * 8 ) -1 ;

	while(num)
	{
		if (num & 1 )
			rev = rev | 1<<pos;
		num = num >> 1;
		pos--;
	}

	return rev;
}

int Check_Pwr_of_4(int num)
{

	if ( !(  num &  ( num -1) ) && (num & 55555555) )
		printf("Power of 4 \n");
	else
		printf("Not A power of 4\n");

	return 0;
}
int Check_PositiveorNegative(int num)
{
	if (  num * -1 > num )
		printf("- %d \n",num);
	else
		printf("+ %d \n",num);
	return 0;
}

int PrintAllBits(int num)
{
	int i=0;
	for(i= ( sizeof(int)*8) -1; i>=0 ; i-- )
		printf("%d ", (( num>>i ) & 1 ) );
	printf("\n");
	return 0;
}
int 	PowerOf2_Logic2(int num)
{
	if ( num &  ( num -1 ) )
		printf(" Not A power of 2 \n");
	else 
		printf(" Power of 2 \n");

	return 0;
}

int CountNumberOfSetBits(int num)
{
	int i=0,count=0;
	for(i= ( sizeof(int)*8) -1; i>=0 ; i-- )
		if (  (( num>>i ) & 1  ) == 1 )
			count++;
	printf("Total Set Bit Count = %d\n",count);
	return count;
}
int PowerOf2(int num)
{

	// Logic is if Power 2, only one bit is 1 all are zero 

	if ( CountNumberOfSetBits(num)  == 1  )
		printf(" Power Of 2\n");
	else 
		printf("Not A Power of 2\n");

	return 0;
}
int odd_or_even(int num)
{
	// Logic is, if bit is odd, it should have 0th bit is 1 
	if ( num & 1 )
		printf(" Odd \n");
	else 
		printf(" Even Number  \n");
	return 0;
}
