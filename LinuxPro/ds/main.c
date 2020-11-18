#include<stdio.h>
#include<stdlib.h>
void FIFO(int num);
	void reverse_list();
	void print();
	void printMiddle();
struct hi
{
	int num;
	struct hi *link;
};
struct hi *head;

int main()
{

	FIFO(1);
	FIFO(2);
	FIFO(3);
	FIFO(4);
	print();
	reverse_list();
	print();
	printMiddle();
	return 0;
}

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
	{

		head = mem;
		head->link = NULL;
	}

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

void reverse_list()
{

	struct hi *prev,*next,*curr;

	//						1 2 3 4 

	prev = NULL;
	curr = head;

	while( curr != NULL )
	{

		next = curr->link;
		curr->link = prev;
		prev = curr;
		curr = next;
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
