#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<error.h>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
static	char buf[100];
	int i,j;
	mkfifo("fifo",0777);
	while(1)
	{
	i=open("fifo",O_WRONLY);
		printf("enter for fifo\n");
		fgets(buf,100,stdin);
		if(write(i,buf,strlen(buf))!=-1)
		{
			printf("write success\n");
		}
close(i);
	}
}
