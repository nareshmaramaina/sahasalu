#include<stdlib.h>
#include<stdio.h>
#include<string.h>
check(char temp)
{
	if((temp>='a')&&(temp<='f'))
		return (int)(temp-87);
	else if((temp>='A')&&(temp<='F'))
		return (int)(temp-55);
	else if((temp>=48)&&(temp<=57))
		return (int)(temp-48);
	else
	{
		printf("enter a correct string:");
		exit(0);
	}
}
int main()
{
	char num[13];
	int res=0,temp,i,j=0,k;
	printf("enter the number\n");
	scanf("%s",num);
	k=strlen(num)-1;
	for(i=k;i>=0;i--,j+=4)	
	{
		temp=check(num[i]);
		res=res+(temp<<j);
	}
	printf("result=%d\n",res);
}

