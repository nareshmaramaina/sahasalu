#include"headers.h"
int main()
{
	char i;
	/*adding elemnts*/
	while(1)
	{
		printf("1)add element\n2)display element\n3)delete element\n4)exit\n");
		printf("please enter:");
		while((i=getchar())==10);
		getchar();		
		switch(i)
		{
			case '1':add();
				 break;
			case '2':display();
				 break;
			case '3':delete();
				 break;
			case '4':
				 //my_sync();
				 return 0;
			default : printf("plz choose valid option\n");
		}

	}
}
void add(void)
{
	tree *temp,*new=NULL;
	char name[20];
	int num;
	new=malloc(1*sizeof(tree));
	printf("enter ur name\n");
	scanf("%s",new->name);
	printf("enter ur num\n");
	scanf("%d",&new->num);
	if(head!=NULL)
	{
		temp=head;
		while(temp->link)
			temp=temp->link;
		temp->link=new;
		new->link=0;
	}
	else
	{
		head=new;
		new->link=0;
	}
	return;
}
void display(void)
{
	int i=0;
	tree *temp=NULL;
	temp=head;
	printf("\n**************************************************\nSTUDENT NAME \t ROLL NUMBER\n");
	while(temp)
	{
		printf("%d.%s\t\t %d\n",temp,temp->name,temp->num);
		temp=temp->link;
	}
	for(temp=head,i=0;temp!=NULL;temp++)	
		printf("%d.%s\t\t %d\n",temp,temp->name,temp->num);
	printf("\n**************************************************\n");
	return;

}
void delete(void)
{
	int delnum;
	tree *temp=head,*prev;
	printf("please enter roll number for delete the element\n");
	scanf("%d",&delnum);
if(!head)
{
printf("There are no elements\n");
return;
}
	if(temp->num==delnum)
	{
		head=temp->link;
		printf("%d number is deleted\n",temp->num);
		free(temp);
		return;
	}
	while(temp!=NULL)
	{
		if(temp->num==delnum)
		{
			prev->link=temp->link;
			printf("%d number is deleted\n",temp->num);
			free(temp);
			return;
		}
		else prev=temp;
		temp=temp->link;
	}
	printf("%d number not found\n",temp->num);
	free(temp);
	return;
}
