#include<stdio.h>
#include<string.h>
int i=0;
void swap(char *str,char *str1)
{
	printf(" Start   %c %c  \n", *str,*str1);
	char ch;
	ch=*str;
	*str=*str1;
	*str1=ch;
	printf(" End i = %d    %c %c  \n", ++i,*str,*str1);
}
void possi(char *str,int l,int n)
{
	int i;
	if(l==n)
		printf("%s\n",str);
	else
	{
		for(i=l;i<=n;i++)
		{
			swap(str+i,str+l);
			possi(str,l+1,n);
			swap(str+i,str+l);
		}
	}
}


int main()
{
	int i,j,k;
	char str[10],ch;;
	printf("enter the stri8ng\n");
	scanf("%s",str);
	possi(str,0,strlen(str)-1);
}
