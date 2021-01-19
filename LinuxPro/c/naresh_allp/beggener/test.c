#include<stdio.h>
#include<string.h>
void test(char *temp)
{
int i=0;
char str[][7]={"naresh","suresh","mahesh","balesh","shirish","sattish"};
for(i=0;temp[i];i++)
{
if(temp[i]>='A'&&temp[i]<='Z')
temp[i]=temp[i]+32;
}
for(i=0;i<6;i++)
{
	if(!(strcmp(temp,str[i])))
	{
		printf("%s is a member\n",temp);
			return;
	}
}
printf("%s***!!!!!____**** sry..! ur not a member\n",temp);

}
