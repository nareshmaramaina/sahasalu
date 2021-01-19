#include<stdio.h>
int main()
{
	int x,y,z;
	printf("enter the value\n");
	scanf("%d",&x);
	for(z=2;z<=x;z++)
	{
		for(y=2;y<z;y++)
		{
			if(z%y==0)break;
		}
		if(y>=z)printf("%d,",y);
	}
}
