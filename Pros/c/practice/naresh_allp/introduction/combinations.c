#include<stdio.h>
#include<string.h>
int recur(int len)
{
	int res;
	if(len==1)
		return 1;
	else 
	res=len*recur(len-1);
}
void swapped(char *str,int i)
{
str[i]=str[i+1];
str[i+1]=str[i];
}
int main()
{
	int len,i,j;
	char str[10];
	printf("enter the string\n");
	scanf("%s",str);
	len=strlen(str);
	len=recur(len);
	printf("total possible combinations %d\n",len);
	for(i=0;i<len;i++)
	{
swapped(str,i);
		printf("%s\n",str);

	}
}
