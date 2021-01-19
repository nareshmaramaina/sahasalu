#include<stdio.h>
#include<stdlib.h>
#pragma pack(3)
struct node 
{
char i;
int data;
	struct node *link;
};
struct node *head=NULL;

void add()
{
	struct node *new=NULL;
	struct node *temp;
	int data;
	printf("enter the data\n");
	scanf("%d",&data);
	new = malloc(sizeof(struct node));
	new->data = data;
	if(head ==NULL)
	{
		head=new;
		new->link =NULL;
	}
	else
	{
		new->link=head;
		head=new;
	}
return;
}
void display()
{
	struct node *temp=NULL;
	temp=head;
printf("\n********data******\n");
	while(temp!=NULL)
	{
		printf("%d\n",temp->data);
		temp=temp->link;
	}

}

int main()
{
struct node *ptr;
printf("ptr= %lu\n",ptr);
ptr++;
printf("ptr= %lu\n",ptr);
	display();
}
