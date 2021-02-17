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
struct hi *head=NULL,*end;
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

int List_Even_Add()
{
	/* Procedure 
 * Take end, Final_end, prev, curr or tmp, last, variables
 * First Traverse loop to set end element , end is fixed 
 * 	If head is odd then  copy next link to  head, move curr link to end of the list and make it link as NULL, then put  prev and curr is head 
 *     if head is odd but head, this situation, importantely take a copy of current link to last, then move current link to end of the list make it as null,   then set  previous link to last and curr,
 *    else if if even just increamnt pointer and take a copy of prev
 */
 	struct hi *tmp=head;
	struct hi *end,*Final_end,*prev,*last;
	while( tmp -> link != NULL )
		tmp = tmp->link;

	Final_end=end=tmp;
	tmp =  head;
	prev=tmp;

	while ( tmp != end )
	{
		if ( tmp->num %2 != 0 )
		{
			if ( tmp == head)
			{
				//last=tmp->link;
				//prev=tmp->link;
				head = tmp->link;
				Final_end->link = tmp;
				Final_end->link->link = NULL ;
				//Final_end=tmp;
				Final_end=Final_end->link;
				prev=tmp=head;
			}
			else 
			{
				last=tmp->link;
				Final_end->link=tmp;
				Final_end->link->link = NULL ;
				Final_end=Final_end->link;
				tmp=prev->link=last;
			}
		}
		else 
		{
			prev=tmp;
			tmp=tmp->link;
		}
	}
	print_even_and_odd();
	return 0;
}
int print_even_and_odd()
{

	struct hi *even, *odd, *tmp =head;
	printf("Arraged as even and odd \n");
	print();
	while(tmp)
	{
		if ( tmp->num % 2 != 0 )
		{
			odd=tmp;
			even=tmp=head;
			while(tmp->link != odd)
				tmp = tmp->link;
			tmp->link=NULL;

			break;
		}
		tmp=tmp->link;
	}

	head=odd;
	printf("Odd\n");
	print();
	head=even;
	printf("Even\n");
	print();
	return 0;
}

int main()
{
	AddAtend(1);
	AddAtend(1);
	AddAtend(2);
	AddAtend(3);
	AddAtend(4);
	AddAtend(5);
	AddAtend(6);
	AddAtend(7);
	AddAtend(8);
	AddAtend(9);
	AddAtend(10);
	AddAtend(1);
	AddAtend(1);
	AddAtend(2);
	AddAtend(3);
	AddAtend(4);
	AddAtend(5);
	AddAtend(6);
	AddAtend(7);
	AddAtend(8);
	AddAtend(9);
	print();
	List_Even_Add();
	return 0;
}
void print()
{
	struct hi *tmp=head;

	while(tmp)
	{
		printf("%d,",tmp->num);
		tmp=tmp->link;
	}
	putchar('\n');
	return;
}
