#include<stdio.h>
int main(int argc, char *argv[])
{
int i=0;
char n[10]="naresh";
int *k,*j;
if( argv[1] == n )
printf("success\n");
puts(argv[1]);
printf("%d\n",strcmp(argv[1],"naresh"));
}
