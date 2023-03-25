#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<error.h> 
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
int fd;
char buf[20];
//mkfifo("fifo2",0777);
//fflush(stdout);
if((fd=open("fifo3",O_RDONLY))==-1)
{
perror("open");
exit(0);
}
/*if(fork()==0)
{*/
if(read(fd,buf,20)==-1)
perror("error:");
else 
printf("read success %s\n %s\n",buf,buf+11);
}
