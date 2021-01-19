#include<stdio.h>
#define MAX(fun,dtype) dtype fun(dtype x,dtype y){return x>y?x:y;}
int main()
{
int p;
float q;
double r;
MAX(max_int,int)
MAX(max_float,float)
MAX(max_double,double);
p=max_int('A',9.88);
q=max_float(7.4,5.7);
r=max_double(12.34,13.54);
printf("p=%d,q=%.2f,r=%.5f\n",p,q,r);
}
