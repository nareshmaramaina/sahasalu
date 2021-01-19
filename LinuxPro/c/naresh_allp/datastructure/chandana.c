#include<stdio.h>
#include<stdlib.h>
 
struct node 
{
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
	new->link =NULL;

	if(head ==NULL)
		head=new;

	else
	{
		temp =head;
		while(temp->link!=NULL)
			temp=temp->link;
		temp->link = new;
	}

}

void display()
{
	struct node *temp=NULL;
	temp=head;

	while(temp!=NULL)
	{
		printf("%d",temp->data);
		temp=temp->link;
	}

}

int main()
{
	add();
	add();
	add();
	display();
}
int delete(int data)
{
struct node *temp;
struct node  *prev;

temp = head;


while(temp->data != data)
{
temp = temp->link;

}


if(temp->data == data)
break



}





}




