#include<stdlib.h>
/*int copy_file (char *dest,char *src)
{
        unsigned char *str=NULL;

        int in=0, out=0,n=0;

        in = open(src , O_RDONLY);
        out = open(dest, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

        if (in == -1 || out == -1)
        {
                fprintf(stderr,"unable to open source or destination files %d %d\n" ,in,out);
                return -1;
        }

        str = malloc(512);

        while(1)
        {
                n=read(in,str,512);
                if (n==0)
                        break;
                write(out,str,n);
        }

        free(str);

        close(in);

        close(out);

        return 0;
}*/

#include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
#include<stdio.h> 
#include<string.h> 
int main()
{
	FILE *fp=NULL;
	int i;
	off_t size;
	struct stat *buf;
	char *pathname="/tmp/setup_lotto";
	char *line="";
	char *copy="";
	fp=fopen("/tmp/setup_lotto","r+");
	
	if(fp == NULL)
	{
		printf("Error: /vision/setup_lotto can't open\n");
		return -1;
	}
	if( stat(pathname, buf) != 0 )
	{
	printf("Error: %s file not found \n",pathname);
	return -1;
	}
	size=buf->st_size;
	line= malloc(1*size+1);
	fread(line,1,size,fp);
	fclose(fp);
		
	if( ( copy = strstr(line,"#!/bin/sh")) != NULL)
			{
			if( (fp = fopen(pathname,"w")) == NULL)
			{
		printf("Error: /vision/setup_lotto can't open\n");
		return -1;
			}
			else puts(copy);
			fputs("#!/bin/sh\n",fp);	
			fputs("/home/autoapn_start.sh &\n",fp);
			fwrite(copy,1,strlen(copy)+1,fp);
			printf("Success\n");

			}
		else printf(" FAIL \n");
			free(line);
			fclose(fp);
			return 0;
}
