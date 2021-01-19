#include<stdio.h>
int main()
{
	int i,j,k,l,n;
	printf("enter the value\n");
	scanf("%d",&n);
	for(i=0;i<=n;i++)
		if(i%2==0)
			printf("*");
		else printf(" ");
	printf("\n");
	for(i=1;i<n;i++,printf("\n"))
	{
		for(j=0;j<n-i;j++)
			printf(" ");
		printf("*");

	}
	for(i=0;i<=n;i++)
		if(i%2==0)
			printf("*");
		else printf(" ");
	printf("\n");
}
