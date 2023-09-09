#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct kundu{
struct kundu *link;
char data;
}valid;

valid* stack(valid *head,char ch)
{
	valid *ptr=NULL,*temp=NULL;
	ptr=malloc(sizeof(valid));
	if(head== 0)
	{
		head=ptr;
		ptr->data=ch;
		ptr->link=0;
	}
	else
	{
		ptr->link=head;
		ptr->data=ch;
		head=ptr;
	/*	temp=malloc(sizeof(valid));
	
        temp->link=head;
		ptr->data=ch;
		ptr->link=temp->link;
		head=ptr;
		free(temp);*/
	}
	return head;
}
int check(char ch,valid *head)
{
if(head==0){
printf("wrong experssion\n");
exit(0);
}
	if(head->data=='{')head->data='}';
	else if(head->data=='[')head->data=']';
	else if(head->data=='(')head->data=')';
	if(ch==head->data)
		return 1;
	else return 0;
}
valid* destack(valid *head)
{
	valid *temp;
	temp=malloc(sizeof(valid));
	temp=head;
	head=head->link;
	free(temp);
	return head;
}
int main()
{
	int j=0,i;
	char buff[100];
	valid *head=0,*temp;
	printf("enter the experssion\n");
	scanf("%s",buff);
	for(i=0;buff[i];i++)
	{
		if(buff[i]=='{'||buff[i]=='['||buff[i]=='(')
			head=stack(head,buff[i]);
		else if(buff[i]=='}'||buff[i]==']'||buff[i]==')')
		{
			if(check(buff[i],head))
				head=destack(head);
			else
			{
				printf("wrong order\n");
				break;
			}
		}
	}
	if(head==0)
		printf("right order\n");
else printf("need more experssion\n");
	//	temp=malloc(sizeof(valid));
	//	temp=head;
	//	for(;temp;temp=temp->link)
	//		printf("%c\n",temp->data);
}
