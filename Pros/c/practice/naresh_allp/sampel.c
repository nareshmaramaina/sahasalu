#include<stdio.h>
#include<string.h>

int main()
{
	FILE *fd;
	int i=0;
	int j=0;
	char operator[50]="";
	char operator_buff[256]="";
	char other_details_buff[50]="";
	memset(other_details_buff,0,sizeof(other_details_buff));

	fd=fopen("/tmp/revision_operator_details","r");
	if(fd==NULL)
	{
		fprintf(stderr,"Unable to Write the Details into File\n");
		return -1;
	}

	fread(other_details_buff,1,50,fd);
#if DEBUG
	printf("Revision_Operator_Details---->%s\n",other_details_buff);
#endif
	fclose(fd);
	memset(operator_buff,0,sizeof(operator_buff));
	for(i=0;i<25;i++)
	{
		if (other_details_buff[i]!=',')
			operator_buff[i]=other_details_buff[i];
		else
			break;
	}

	for(i=0;operator_buff[i];i++)
		if(isupper(operator_buff[i]))
			operator_buff[i]+=32;
	if((strstr(operator_buff,"airtel")==0)
			||(strstr(operator_buff,"idea")==0)
			||(strstr(operator_buff,"vodafone")==0)
			||(strstr(operator_buff,"bsnl")==0)
			||(strstr(operator_buff,"videocon")==0)
			||(strstr(operator_buff,"uninor")==0)
			||(strstr(operator_buff,"reliance")==0)
			||(strstr(operator_buff,"aircel")==0))
		strcpy(operator,operator_buff);
	else if(strcmp(operator_buff,"tata")==0)
		strcpy(operator,"Docomo");
	else strcpy(operator,"ERROR");
	printf(" operator = %s \n ", operator);

#if 0
        if(strstr(operator_buff,"airtel")!=NULL || strstr(operator_buff,"Airtel")!=NULL || strstr(operator_buff,"AIRTEL")!=NULL || strstr(operator_buff,"AirTel")!=NULL)
        {
                strcpy(operator,"airtel");

        }

        else if(strstr(operator_buff,"idea")!=NULL || strstr(operator_buff,"Idea")!=NULL || strstr(operator_buff,"IDEA")!=NULL || strstr(operator_buff,"!dea")!=NULL)
        {
                strcpy(operator,"Idea");

        }

        else if(strstr(operator_buff,"reliance")!=NULL || strstr(operator_buff,"Reliance")!=NULL || strstr(operator_buff,"RELIANCE")!=NULL)
        {
                strcpy(operator,"Reliance");

        }

        else if(strstr(operator_buff,"vodafone")!=NULL || strstr(operator_buff,"Vodafone")!=NULL || strstr(operator_buff,"VODAFONE")!=NULL)
        {
                strcpy(operator,"Vodafone");

        }

        else if(strstr(operator_buff,"uninor")!=NULL || strstr(operator_buff,"Uninor")!=NULL || strstr(operator_buff,"UNINOR")!=NULL)
        {
                strcpy(operator,"Uninor");

        }

        else if(strstr(operator_buff,"aircel")!=NULL || strstr(operator_buff,"Aircel")!=NULL || strstr(operator_buff,"AIRCEL")!=NULL)
        {
                strcpy(operator,"Aircel");

        }

        else if(strstr(operator_buff,"tata")!=NULL || strstr(operator_buff,"Tata")!=NULL || strstr(operator_buff,"TATA")!=NULL)
        {
                strcpy(operator,"Docomo");

        }

        else if(strstr(operator_buff,"bsnl")!=NULL || strstr(operator_buff,"Bsnl")!=NULL || strstr(operator_buff,"BSNL")!=NULL)
        {
                strcpy(operator,"bsnl");

        }

        else if(strstr(operator_buff,"videocon")!=NULL || strstr(operator_buff,"Videocon")!=NULL || strstr(operator_buff,"VIDEOCON")!=NULL)
        {
                strcpy(operator,"Videocon");

        }
        else
                strcpy(operator,"ERROR");

#endif


	return 0;
}

