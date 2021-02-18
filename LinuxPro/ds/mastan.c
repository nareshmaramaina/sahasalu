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

int List_Even_Odd()
{
/* Procedure 
- * Take end, Final_end, prev, curr or tmp, last, variables
- * First Traverse loop to set end element , end is fixed 
- *     If head is odd then  copy next link to  head, move curr link to end of the list and make it link as NULL, then put  prev and curr is head 
- *     if head is odd but head, this situation, importantely take a copy of current link to last, then move current link to end of the list make it as null,   then set  previous link to last and curr,
- *    else if if even just increamnt pointer and take a copy of prev
- */

struct hi *curr,*end,*tail,*prev;

prev = end = curr = head;

while ( end -> link != NULL )
end=end->link;

tail = end;
// 1 1 2  3  4  5 6 

while ( curr != end )
{
	if ( curr -> num % 2 != 0 )
	{
		if (  curr == head ) 
		{
			head = curr->link;
			tail->link=curr;
			tail->link->link=NULL;
			tail = tail->link;
			curr = prev = head;
		}
		else 
		{
			tail->link = curr;
			prev->link=curr->link;
			tail->link->link=NULL;
			tail = tail->link;
			curr=prev->link;	
		}
	}
	else 	
	{
		prev = curr;
		curr = curr->link;
	}
}


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
	List_Even_Odd();
	print();
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
