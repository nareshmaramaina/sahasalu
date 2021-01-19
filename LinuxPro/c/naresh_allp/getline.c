#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int main()
{
char *lineptr=NULL;
size_t n=10;
int ret=0;
        char contact[15]="";
        char phno[30]="";
        char msg[200]="";

        printf("Enter Contact No:+91\n");
//	scanf("%s",phno);
	//getline(&lineptr,&n,stdin);
	read(1,phno,30);
	fflush(stdin);
	//printf("******* %s **********\n",phno);
	strcpy(contact,phno);
        if(strlen(contact) > 10)
        {
                printf("phone number not valid\n");

                printf("phone number not valid\n");
                return 0;
        }
	puts(contact);
	lineptr=NULL;        
	printf("Enter Msg: ");

	getline(&lineptr,&n,stdin);
	strcpy(msg,lineptr);

        if(strlen(msg)>=161)
        {
                if(msg[strlen(msg)-1] == '\n')
                        msg[strlen(msg)-1] = '\0';
        }

printf(" msg = %s\n",msg);
return 0;
}
