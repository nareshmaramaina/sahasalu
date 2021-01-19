#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node 
{
	int number;
	char Name[128];
	struct node *link;
}List;
List *Add(List *head,int number, char *Name);
int main()
{
	int number;
	char Name[128];
	List *head=NULL;
	//	head = malloc(sizeof(List));
	while(1)
	{

		memset(Name,0,sizeof(Name));
		printf("Enter Student Details\n");
		scanf("%d%128s",&number,Name);
		head = Add(head,number,Name);
		print(head);
	}

	return 0;
}

//1 2 3 4 5 
// Head= 1, Link = NULL 2  1  
List *Add(List *head,int number, char *Name)
{
	List *Node;
	List *tmp;
	Node = malloc(sizeof(List));
	if ( Node == NULL )
	{
		printf("Allocation Failed\n");
		return -1;
	}
	Node->number = number;
	strcpy(Node->Name,Name);
	Node->link=NULL;

	if ( head == NULL )
	{
		head=Node;
		printf("First Insert\n");
	}	       
	else 
	{	
		//	for ( tmp= head->link; tmp != NULL ; tmp = tmp->link );
		tmp = head;
		while ( tmp->link != NULL )
			tmp = tmp->link;
		tmp->link=Node;
	}
	return head;
}
int print(List *head )
{	
	List *tmp;
	for ( tmp=head; tmp != NULL ; tmp = tmp->link )
	{
		printf(" number %d Name = %s\n",tmp->number,tmp->Name);
	}
	return 0;
}
