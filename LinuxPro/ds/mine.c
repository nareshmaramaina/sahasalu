#include<stdio.h>
#include<stdlib.h>
void FIFO(int num);
void reverse_list();
void print();
void printMiddle();
void LIFO(int num);
struct hi
{
	int num;
	struct hi *link;
};
struct hi *head=NULL;
void Delete_mid()
{

	struct hi *slow,*fast,*prev;
	if ( head == NULL )
		printf("There is No Elements delete\n");
	else if ( head -> link == NULL || head -> link -> link == NULL )
	{
		prev = head;
		head = head->link;
		printf("Deleting = %d\n",prev->num);
		free(prev);
		prev=NULL;
	}
	// prev		Slow   Fast 
	// 1 		2  	3  	4 5 6 7 

	else 
	{
		prev=slow=fast=head;
		while ( fast -> link != NULL &&  fast -> link -> link != NULL )
		{

			fast = fast -> link -> link;
			prev=slow;
			slow = slow->link;

		}
		printf(" Deleting Middle Node is %d\n", slow->num);
		prev->link=slow->link;

		free(slow);
		slow=NULL;	
	}
	return;
}
void Delete_Num(int num)
{
	struct hi *tmp,*curr;

	if ( head-> num == num )
	{
		tmp = head;
		head = head->link;
		free(tmp);
		return;
	}
	for ( curr = head; curr != NULL ; curr = curr->link )
	{
		if (  ( curr ->link -> num ) == num )
		{
			tmp = curr->link;
			curr -> link = curr->link->link;
			free ( tmp);
			return; 
		}

	} 	
	/*	for(curr=head; curr->link != NULL   ; curr=  curr->link )
		{
		if ( curr->link -> num == num )

		{

		tmp = curr->link;

		curr->link =tmp->link;
		free(tmp);
		return; 	
		}

		}	*/
	return;
}
int Addatbeg(int num)
{

	struct hi *new;

	new = calloc(1,sizeof(struct hi));

	if ( new == NULL )
	{
		printf("Allocation Failed\n");
		return -1;
	}

	new->num=num;

	new->link=head;

	head=new;

	return 0;
}
int AddAtend(int num)
{

	struct hi *copy,*new;

	new = calloc(1,sizeof(struct hi));
	if ( new == NULL )
	{
		printf("Allocation Failed\n");
		return -1;
	}

	new->num = num;
	new->link = NULL;

	if ( head == NULL )
		head=new;

	else 

	{

		//		1 2 3 4 NULL
		copy = head;
		while(copy->link)
		{
			copy=copy->link;
		}
		copy -> link = new;
	}
	return 0;
}
int main()
{
	AddAtend(4);
	AddAtend(3);
	AddAtend(2);
	AddAtend(1);
	AddAtend(0);
	/*	AddAtend(5);
		AddAtend(6);
		AddAtend(4);
		AddAtend(7);
		AddAtend(5);
		AddAtend(5);
		AddAtend(6);
		AddAtend(4);
		AddAtend(3);
		AddAtend(4);
		AddAtend(5);
		AddAtend(6);
		AddAtend(7);*/

	//Addatbeg(12);
	print();
	//	Delete_Num(2);
	//Delete_mid();
	MyReverse();
	print();
	//printMiddle();
	//reverse_list();
	print();
	return 0;
}
// 1,2,3,4,5,6,7
void FIFO(int num)
{
	struct hi *mem,*copy;

	mem = malloc(sizeof(struct hi) * 1 );

	if ( mem == NULL )
	{
		puts("mem fialed");
		return; 
	}
	mem->num = num;
	mem->link = NULL;

	if ( head == NULL )
		head = mem;

	else 
	{

		copy = head;

		while(copy->link)
			copy = copy->link;

		copy->link = mem;	

	}
	puts("added");
	return ;

}
void print()
{

	struct hi *copy;
	copy = head;

	puts("************************");
	while(copy != NULL )
	{
		printf("Num = %d\n",copy->num);
		copy = copy->link;

	}

	puts("************************");
	return;
}
void LIFO(int num)
{
	struct hi *mem,*copy;

	mem = malloc(sizeof(struct hi) * 1 );

	if ( mem == NULL )
	{
		puts("mem fialed");
		return;
	}
	mem->num = num;

	if ( head == NULL )
	{

		head = mem;
		head->link = NULL;
	}

	else
	{



		copy = head;

		head = mem;

		mem->link = copy;


	}
	puts("added");
	return ;

} 

int delete(int num)
{

	struct hi *tmp,*p;


	if( head->num == num )
	{
		printf(" %d deleted \n",num);
		tmp=head;
		head = head->link;
		free(tmp);
		return 0;
	}

	tmp = head;
	while( tmp->link != NULL)
	{

		if ( tmp->link->num == num )
		{

			printf("Deletng %d\n",num);

			p = tmp->link;

			tmp->link = p->link;

			free(p);

			return 0;
		}
		tmp = tmp->link;

	}

	printf(" %d not found \n",num);
	return 0;
}

void MyReverse()
{

	struct hi *prev,*curr,*next;
	// 1 2 3 4 5 
	// 2 1(NULL) 1 should store at prev  3 4 5 
	// 
	prev=NULL;
	curr=head;
	while(curr)
	{
		next = curr->link;

		curr->link = prev;

		prev = curr; 	

		curr = next;
	}

	head = prev;
	return;
}

void reverse_list()
{

	struct hi *prev,*next,*curr;

	prev = NULL;
	curr = head;

	while( curr != NULL )
	{

		next = curr->link;		
		curr->link = prev;
		prev = curr;
		curr = next;

		// 1 2 3 4 5 
		//   prev = NULL Next = 2 [ Have List ]  curr->link = 1 [ prev = NULL ]  prev = curr [ 1 ]  curr [ Next 2 [ Have List ]  ] 

		//   prev = 1, next = 3 , curr -> link = prev [ 1]  , prev = 2 , curr = 3 

		//   NULL 1 2 3 4 5 6 7 8 9 
	}
	head = prev;
	return;
}
void printMiddle()
{

	struct hi *slow_ptr = head;
	struct hi *fast_ptr = head;
	if (head!=NULL)
	{
		while (fast_ptr != NULL && fast_ptr->link != NULL)
		{
			fast_ptr = fast_ptr->link->link;
			slow_ptr = slow_ptr->link;
		}
		printf("The middle element is [%d]\n\n", slow_ptr->num);
	}

}
