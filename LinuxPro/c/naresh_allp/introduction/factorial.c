#include<string.h>
#include<stdio.h>
int main()
{
	int len,temp=1;
	char str[30];
	printf("enter the string\n");
	scanf("%s",str);
	len=strlen(str);
	while(len)
		temp=temp*len--;
	printf("%d\n",temp);

}
