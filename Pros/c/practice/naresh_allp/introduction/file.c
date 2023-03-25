#include<string.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
	int pos,i,j,k=0,len;
	char str[10];
	static char *ptr,buff[11][20];
	FILE *fp,*fp1;
	fp=fopen("datafile","r+");
	fseek(fp,0,SEEK_END);
	pos=ftell(fp);
	rewind(fp);
	ptr=malloc(pos*sizeof(char));
	fread(ptr,pos+1,1,fp);
	printf("%s",ptr);
	for(i=0;i<11;i++,k++)
	{
		for(j=0;ptr[k]!=' ';j++)
			buff[i][j]=ptr[k++];
		//if(ptr[k+1]=='\0')
		//break;
	}
	printf("enter the string for searching\n");
	scanf("%s",str);
	len=strlen(str);
	for(k=0;k<i;k++)
	{
		if(str[0]==buff[k][0])
		{
			for(j=1;j<len;)
			{
				if(str[j]==buff[k][j])
					j++;
				else
					break;
			}
			printf("%s\n",buff[k]);
		}
		/*for(j=0;j<strlen(buff[k]);j++)
		  {
		  if(str[0]==buff[k][])
		  {
		  printf("%s\n",buff[k]);
		  break;
		  }
		  }*/
	}
}
