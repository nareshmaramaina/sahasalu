#include<stdio.h>
#define MAX(FNAME,DTYPE) (DTYPE X, DTYPE Y) {return X>Y ?X:Y;}
MAX (max_int,int)
MAX (max_float, float)
MAX (max_double, double)
int main ( )
{
int p;
float q;
double r;
p=max_int(3,9) ;
q=max_float(7.4,5.7) ;
r=max_double(12.34,13.54) ;
printf("p = %d,q = %.2f,r%.2lf\n",p,q,r);
}
