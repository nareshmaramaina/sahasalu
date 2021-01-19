#include<stdio.h>
int main()
{
int i,j,k,l,n;
printf("enter the value\n");
scanf("%d",&n);
for(i=1,l=1;i<=n;i++,l++,printf("\n"))
{
for(j=n-i;j<=n;j++)
printf(" ");
printf("*");
for(k=0;k<=(n-l);k++)
printf(" ");
for(k=0;k<(n-l);k++)
printf(" ");
printf("*");
}
for(i=0;i<=n+1;i++)
printf(" ");
printf("*\n");

}
