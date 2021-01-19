#include <header.h>

int main(int argc,char  *argv[])
{
grep_name();

}
int grep_name()
{
	FILE *fp;
	int i=0;
	char *line=NULL,*str;
	size_t len=20;
	char buff[20]="";
	fp = fopen("/etc/visiontek_release","r");
	if(fp == NULL)
	{
		fprintf(stdout,"Patch Details Unavailable\n");
		return -1;
	}
	while((getline(&line, &len, fp)) > 0)
	{
		if((str = (char *)strstr(line,"PATCH_VERSION=")) != NULL)
		{
			//		strcpy(buff,line);
			str=str+14;
			for(i=0;i<10;i++)
			{
				if(str[i]=='\n')
				{
					break;
				}
				buff[i]=str[i];
			}



			buff[i]='\0';
			printf("buff=%s\n",buff);
			break;
		}

	}

	line=NULL;
	fclose(fp);
	return 0;
}
