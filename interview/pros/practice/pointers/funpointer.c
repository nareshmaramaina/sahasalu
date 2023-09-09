#include<stdio.h>
int new ( int a,int b)
{
	printf(" IAM in struct\n");
	return a*b;
}

struct fun 
{
	int (*new) (int , char );
	char num;
};

void main()
{

	struct fun jj;
	float (*fp) (int, float);

	float add(int,float),result;

	fp=add;
//	printf("%f\n",result);
	result=(*fp) (5,6.6);
	printf("%f\n",result) ;

}

float add(int a, float b)
{
	static int i=1;
	if(i++==1)
		printf(" again = %f =",add(1,3));
	return (a+b) ;
}


