#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct x
{
	int num;
	char name[20];
	struct x *link;
}tree;
tree *head=NULL;
void add(void);
void display(void);
void delete(void);
