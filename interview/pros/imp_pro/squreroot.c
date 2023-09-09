//#include<math.h>
#include<stdlib.h>
#include<stdio.h>
    double square_root(int num) {
      double x1 = (num*1.0 ) / 2;
      double x2= (x1 + (num / x1)) / 2;
printf("%lf    %lf\n",x1,x2);
      while(abs(x1 - x2) >= 0.0000001) {
        x1 = x2;
        x2 = (x1 + (num / x1)) / 2;
printf("%lf    %lf\n",x1,x2);
      }
      return x2;
    }
int main()
{
int num;
 int i;
double j;
printf("enter the number\n");
scanf("%d",&num);

printf("%lf\n",square_root(num));


/*for(i=num/2;i>1;i--)
{
//if(num/i==i&&num%i==0)break;
if(num/i==i)
{
j=num%i;
j=j+i;
break;
}
}
//if(i>=2)
printf("root power of that is %f\n",j);
//else printf("no roots are available for %d\n",num);
//printf("%lf\n",sqrt(num));*/
}


