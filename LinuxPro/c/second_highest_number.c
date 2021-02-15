#include<stdio.h>
#include<limits.h>
int main()
{
	int first,second;
	first=second=INT_MIN;
	int arr[]={2,0,-1,-2,-3,1},size,i;
	size = sizeof(arr) / sizeof(*arr);

	printf(" Size = %d \n",size );

	for ( i =0 ; i< size ;i++)
	{
		if ( arr[i] > first )
		{
			second = first;
			first = arr[i];
		}
		else if ( arr[i] > second && arr[i] != first )
		{
			second = arr[i];
		}
	}

	printf( " %d \n", second);
}
