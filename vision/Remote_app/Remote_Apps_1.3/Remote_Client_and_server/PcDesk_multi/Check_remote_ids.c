#include<header.h>

int  Check_Remote_Id(char *clientid)
{
	FILE *fp;
	size_t len=0;
	char *str=NULL;
	int ret = -1;
	fp = fopen("Remote_IDs.txt","r");
	if ( fp == NULL )
	{
		fprintf(stdout,"Remote_ids.txt file not found, So Going to Default behaviour\n");
		return 0;
	}

	while((getline(&str,&len,fp)) != -1)
		if  (strstr(str,clientid) != NULL )
			ret = 0;

	free(str);
	str=NULL;
	fclose(fp);

	return ret;
}

