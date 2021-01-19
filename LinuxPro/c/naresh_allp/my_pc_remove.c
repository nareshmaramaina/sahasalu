#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int i=0,j=0,flag=0,for_flag=0;;
	char *command;
	char cwd[1024];
	char check[100]="";
	int ret=0;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if(strcmp(cwd,"/")==0 || strcmp(cwd,"/home")==0)	
		{
			printf("remove operation not allowed in current working directory\n");
			return 0;
		}
	}



	for(i=1;i<argc;i++)
	{
		if((strcmp(argv[i],"-rf")==0) || (strcmp(argv[i],"-r")==0))
		{
			flag=1;
			break;
		}
	}

	command=calloc(15,1);

	if(flag)
	{
		strcpy(command,"rm_old -rf");
	
		for(i=1;i<argc;i++)	
		{

			if((strcmp(argv[i],"-rf")==0) || (strcmp(argv[i],"-r")==0))
				continue;

			if(argv[i][0]=='/' && strstr(argv[i],"/home/naresh") == NULL)
			{
				printf("Permission Denied: %s is std directory\n",argv[i]);
				continue;
			}
			else 
			{	
				command=realloc(command,(strlen(command)+strlen(argv[i]))+1 );
				sprintf(command,"%s %s",command,argv[i]);
			}

		}
		puts(command);
	}




	else if(flag==0)
	{
		strcpy(command,"rm_old ");
		for(i=1;i<argc;i++)
		{	
			command=realloc(command,(strlen(command)+strlen(argv[i]))+1 );
			sprintf(command,"%s %s",command,argv[i]);
		}
		puts(command);
	}

//	ret=system(command);

	return 0;	
}

