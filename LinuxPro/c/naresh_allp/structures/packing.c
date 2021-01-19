#include<stdio.h>
struct size1
{
char i[21];
int *m;
char j;
int k;
//int *m;
//char *l;
};
int main()
{
struct size1 var;
printf("%ld\n",sizeof(struct size1));
printf("char =%ld\nint =%ld\n,char =%ld\nint =%ld\nchar=%ld\n",&(var.i[0]),&var.m,&var.j,&var.k,&var.o);
return 0;
}
