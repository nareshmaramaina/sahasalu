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