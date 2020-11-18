#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
int num;
printf("Please Enter a dec num: \t");
scanf("%d",&num);
int i,tmp;
for(i=(sizeof(int)*8)-1; i>=0; i-- )
{
tmp=num>>i;
if( tmp & 1 )
printf("1");
else 
printf("0");

}
putchar(10);
return 0;
}
