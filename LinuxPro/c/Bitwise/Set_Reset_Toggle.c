#include<stdio.h>
int main()
{
	// Power of 2 
	int num,pos;
	while(1)
	{
		printf("Enter A number \n");
		scanf("%d",&num);
		printf("Enter A number \n");
		scanf("%d",&pos);
		PrintAllBits(num);
		//num = SetBit(num,pos);
		//num = ResetBit(num,pos);
		num = ToggleBit(num,pos);
		PrintAllBits(num);

	}
}
// Clear bit  SEt 100 
// 		  010 11 0 00 0 01 10 1 1 Set | reset | Toggle 
// 		   001 
// 		   100
// 		    11
// 100 ,  100   Set Bit

int ToggleBit(int num,int pos)
{
	return num ^ ( 1 << pos ) ;
}
int ResetBit(int num,int pos)
{
	return num &  ( ~ ( 1 << pos ) );
}	
int SetBit(int num,int pos)
{
	return  num |  ( 1 << pos );
}
int PrintAllBits(int num)
{
	int i=0;
	for(i= ( sizeof(int)*8) -1; i>=0 ; i-- )
		printf("%d ", (( num>>i ) & 1 ) );
	printf("\n");
	return 0;
}

