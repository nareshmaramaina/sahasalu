#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student
{
	char name[20];
	char roll[20];
	float marks;
	struct student *next;
};
struct student* input(struct student *ptr);
void print(struct student *);
struct student* edit(struct student *ptr);
struct student* delete(struct student *ptr);
void freeing(struct student *ptr);
static int cnt;
struct student* addatpos(struct student *);
struct student* add(struct student *);
void save(struct student *ptr);
void main()
{
	struct student *ptr=NULL;
	int choice;
ptr=add(ptr);
	while(1)
	{
		printf("1:input\n2:print\n3:edit\n4:delete\n5:addatpos\n6:quit\n");
		printf("enter a choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:ptr=input(ptr);
			       break;
			case 2:print(ptr);
			       break;
			case 3:ptr=edit(ptr);
			       break;
			case 4:ptr=delete(ptr);
			       break;
			case 5:ptr=addatpos(ptr);
			       break;
			/*case 6:save(ptr);
			       break;*/
			case 6:save(ptr);
                              freeing(ptr);
			       return;
			default:printf("enter a correct choice:");
		}
	}
}
struct student* input(struct student *ptr)
{
	if(ptr==NULL)
	{
		ptr=malloc(sizeof(struct student));
		printf("enter a name:");
		scanf("%s",ptr->name);
		printf("enter a roll no:");
		scanf("%s",ptr->roll);
		printf("enter a marks:");
		scanf("%f",&(ptr->marks));
		ptr->next=NULL;
		cnt++;
	}
	else
	{
		struct student *temp=ptr;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=malloc(sizeof(struct student));
		printf("enter a name:");
		scanf("%s",temp->next->name);
		printf("enter a roll no:");
		scanf("%s",temp->next->roll);
		printf("enter a marks:");
		scanf("%f",&(temp->next->marks));
		temp->next->next=NULL;
		cnt++;
	}
	return ptr;
}
void print(struct student *ptr)
{
	while(ptr!=NULL)
	{
		printf("\tname:%s\n",ptr->name);
		printf("\troll no:%s\n",ptr->roll);
		printf("\tmarks:%f\n",ptr->marks);
		printf("\n");
		ptr=ptr->next;
	}
}
struct student* edit(struct student *ptr)
{
	char temp[20];
	struct student *temp1=ptr;
if(temp1==NULL)
{
printf("no data in the list\n");
return ptr;
}
else
	{
printf("enter a name to edit:");
scanf("%s",temp);
		while(temp1!=NULL)
		{
			if(strcmp(temp1->name,temp)==0)
			{
				printf("enter a new name:");
				scanf("%s",temp1->name);
				return ptr;
			}
			temp1=temp1->next;
		}
	}
	printf("no search found:");
	return ptr;
}
struct student * delete(struct student *ptr)
{
	struct student *temp1=ptr,*temp;
	char name[20];
	printf("enter A name to delete:");
	scanf("%s",name);
	if(ptr==NULL)
	{
		printf("no data in the single list:");
		return ptr;
	}
	else
	{
		if(strcmp(name,ptr->name)==0)
		{
			temp=ptr;
			ptr=ptr->next;
			free(temp);
			printf("successfully deleted:\n");
			return ptr;
		}
		else
		{
			while(temp1->next!=NULL)
			{
				if(strcmp(temp1->next->name,name)==0)
				{
					temp=temp1->next;
					temp1->next=temp1->next->next;
					free(temp);
					printf("ur successfully deleted:\n");
					cnt--;
					return ptr;
				}
				temp1=temp1->next;
			}
			printf("no delete found");
			return ptr;
		}
	}
}
void freeing(struct student *ptr)
{
	struct student *temp=ptr;
	while(ptr!=NULL)
	{
		temp=ptr;
		ptr=ptr->next;
		free(temp);
	}
}
struct student* addatpos(struct student *ptr)
{
	int pos,i;
	printf("enter a pos:");
	scanf("%d",&pos);
	struct student *temp,*prev,*current;
	if(pos<=0)
	{
		printf("invalid position:");
		return ptr;
	}
	if(pos<=cnt+1)
	{
		if(pos==1)
		{
			temp=malloc(sizeof(struct student));
			printf("enter a name:");
			scanf("%s",temp->name);
			printf("enter a roll no:");
			scanf("%s",temp->roll);
			printf("enter a marks:");
			scanf("%f",&(temp->marks));
			temp->next=ptr;
			cnt++;
			return temp;
		}
		else
		{
			temp=ptr;
			prev=temp;
			current=temp->next;
			for(i=0;i<pos-2;i++)
			{
				temp=temp->next;
				prev=temp;
				current=temp->next;
			}
			prev->next=malloc(sizeof(struct student));
			printf("enter a name:");
			scanf("%s",prev->next->name);
			printf("enter a roll no:");
			scanf("%s",prev->next->roll);
			printf("enter a marks:");
			scanf("%f",&prev->next->marks);
			prev->next->next=current;
			cnt++;
			return ptr;
		}
	}
	else
	{
		printf("invalid position:");
		return ptr;
	}
}
void save(struct student *ptr)
{
	FILE *fp;
	fp=fopen("filename.txt","w+");
	if(fp==NULL)
	{
		printf("error in file:");
		return;
	}
	while(ptr!=NULL)
	{
		fprintf(fp,"%s\t%s\t%f\n",ptr->name,ptr->roll,ptr->marks);
		ptr=ptr->next;
	}
	fclose(fp);
}
struct student* add(struct student *ptr)
{

	FILE *fp;
struct student *temp1,*temp;
	fp=fopen("filename.txt","r");
	if(fp==NULL)
	{
		printf("error in file:");
		return	NULL;
	}
temp1=malloc(sizeof(struct student));
while(fscanf(fp,"%s%s%f",temp1->name,temp1->roll,&(temp1->marks))!=EOF)
{
if(ptr==NULL)
{
		ptr=malloc(sizeof(struct student));
		strcpy(ptr->name,temp1->name);
		strcpy(ptr->roll,temp1->roll);
		ptr->marks=temp1->marks;
		ptr->next=NULL;
		cnt++;
	}
	else
	{
		while(ptr->next!=NULL)
			ptr=ptr->next;
		temp=malloc(sizeof(struct student));
	         strcpy(temp->name,temp1->name);
	         strcpy(temp->roll,temp1->roll);
		temp->marks=temp1->marks;
		temp->next=NULL;
		cnt++;
ptr->next=temp;
	}
}
free(temp1);
	return ptr;
}
