#include<stdio.h>
#include<stdlib.h>
int main()
{
	int i;
	int arr[100];
	//arr=malloc(sizeof(int));
	for(i=0;i<400000;i++)
	{
		printf("%d ",arr[i]=i+1);
		//		printf("%d\n ",arr1[i]=i+1);
	}
	//printf("%d\n",arr[0]);
	//printf("%d\n",arr[2]);
	return 0;
}
