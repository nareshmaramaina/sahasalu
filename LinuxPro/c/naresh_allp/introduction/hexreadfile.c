#include<stdlib.h>
#include<stdio.h>
#include<error.h>
int main()
{
int i;
char ch;
FILE *fp;
printf("hai");
if((fp=fopen("macro2.s","rb"))==0)
perror("error:");
rewind(fp);
while((ch=fgetc(fp))!=-1)
printf("%c",ch);
}
