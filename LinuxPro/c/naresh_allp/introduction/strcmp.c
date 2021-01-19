#include<string.h>
#include<stdio.h>
int main()
{
char str[20]="naresh",find[20];
printf("enter the string to be find\n");
//fgets(find,20,stdin);
gets(find);
printf("%lu\n",strlen(find));
if(!(strcmp("naresh.c",find)))
printf("success\n");
else printf("fail\n");
}
