#include<string.h>
#include<stdlib.h>
#include<stdio.h>
int opt()
{
int ret=0;
char arr[50]="";
scanf("%s",arr);
ret=atoi(arr);
return ret;
}
int main(int argc,char *argv[])
{
	char num;
//int ret;

/*	if( (( ret=gl11_gsm_select(1,115200)) == 0 ) || ( (ret=gl11_gsm_select(2,115200) ) == 0) );
	else
	{
//while((num=getchar())==10);
		printf("SIM not available\n");
		gl11_iodev_close();
		return  -2;
	}
*/


	while(1)
	{

	fprintf(stdout,"\n\t1) Inbox\n\t2) Outbox\n\t3) Create sms\n\t4)exit\n");
///	num=getchar();
//	getchar();
	num=opt();
		switch(num)
		{ 	

			case 1:
			printf(" IAM option 1\n");	
			 break;

			case 2:  
			printf(" IAM option 2\n");	
			
			break; 

			case 3:	
			printf(" IAM option 3\n");	
			break;
			case 4: return 0;
5
			default: printf("Wrong input\n");

		}
num=0;
	}

	return 0;
}
