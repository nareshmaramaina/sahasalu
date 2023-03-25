#include<string.h>
#include<stdio.h>
#include<stdlib.h>
struct some
{
char ch;
int num;
char *ptr;
};
int main()
{
struct some *naresh;
naresh=malloc(sizeof(struct some));
naresh->ch='k';
naresh->num=12;
naresh->ptr=malloc(sizeof(char));
strcpy(naresh->ptr,"naresk");
printf("%c\t%d\t%s\n",naresh->ch,naresh->num,naresh->ptr);
}
