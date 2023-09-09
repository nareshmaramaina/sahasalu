#include<stdio.h>
int main()
{
	int i,k,j;
	char ch1[]="/\\",ch2[]="\\/";
	printf("enter the number\n");
	scanf("%d",&k);
	for(i=0;i<k;i++)
	{
		for(j=0;j<i;j++)
			printf("%s",ch1);
		printf("\n");
		for(j=0;j<i;j++)
			printf("%s",ch2);
		printf("\n");
	}
}
