/*
 * =====================================================================================
 *
 *       Filename:  containerof.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 15 March 2021 03:07:02  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  M Naresh (C in Depth), naresh.m@visiontek.co.in
 *        Company:  Visiontek
 *
 * =====================================================================================
 */
#include  <stdio.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({         \
		const typeof( ((type *)0)->member ) *__mptr = (ptr); \
		(type *)( (char *)__mptr - offsetof(type,member) );})

struct sample {
	int mem1;
	char mem2;
};
int func(int *ptr)
{
struct sample *kk =	container_of(ptr, struct sample, mem2); // Pointer of member , struct type , member Variable name

	printf(" %d  %c \n", kk->mem1,kk->mem2 );
	return 0;
}
int main(void)
{

	struct sample sample1={400,'M'};

	printf("Address of Structure sample1 (Normal Method) = %p\n", &sample1);

	func(&sample1.mem2);
	return 0;
}
