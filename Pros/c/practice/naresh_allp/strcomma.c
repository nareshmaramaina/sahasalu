#include<stdio.h>
#include<string.h>
int main()
{
int i,k;
char mtr[]="iam,u\niam,rowdy\n,u,yoyo";
char *ptr;

char parts[4][10];
ptr=mtr;

printf(" %s " ,ptr);
for(i=0;i<4;i++)
{
for(k=0;ptr[k]!=',' && ptr[k] != 10  ;k++)
parts[i][k]=ptr[k];
parts[i][k]='\0';
ptr=ptr+k+1;
printf(" \nPrinting parts[%d]=%s\n",i,parts[i]);
}
return 0;

}
