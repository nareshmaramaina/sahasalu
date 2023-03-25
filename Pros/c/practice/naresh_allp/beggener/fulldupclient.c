#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<error.h> 
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
	int fd,i=0;
	char buf[100];
	mkfifo("fifo3",0777);
	fflush(stdout);
	if((fd=open("fifo3",O_RDWR))==-1)
	{
		perror("open");
		exit(0);
	}
	while(1)
{
			if(read(fd,buf,100)==-1)
				perror("error:");
			else 
				printf("recevied:%s\n",buf);
			gets(buf);
			if(write(fd,buf,100)==-1)
				perror("error:");
			else 
				printf("sended\n");

}	}
