#include<stdio.h>
#include<stdlib.h>
int main()
{
int value,row,col;
FILE *fp;
char *str;
fp=fopen("datafile","r+");
fseek(fp,0,SEEK_END);
value=ftell(fp)+1;
rewind(fp);
str=malloc(value*sizeof(char));
fread(str,value,1,fp);
printf("%s",str);

printf("enter the row number\n");
scanf("%d",&row);
printf("enter the coloum number\n");
scanf("%d",&col);
rewind(fp);
fseek(fp,(row-1)*27+(col-1)*2+1,SEEK_CUR);
fputc(66,fp);


}
