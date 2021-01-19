#include<stdio.h>
int main()
{
	int j,res,i=0;
	char ch;
	printf("enter:");
	scanf("%d",&j);
	scanf("%c",&ch);
	scanf("%d",&i);
	switch(ch)
	{
		case '*':res=j*i;break;
		case '/':res=j/i;break;
		case '%':res=j%i;break;
		case '+':res=j+i;break;
		case '-':res=j-i;break;
		default :printf("u entered wrong operand");
			 return 0;
	}
	printf("result=%d\n",res);
}
