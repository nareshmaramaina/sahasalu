#include<stdio.h>

struct A
{
	int a;
	double d;
	char c;
} __attribute__((packed))obj;

int main()
{
	printf("\n %d \n",sizeof(obj));
	return 0;
}
