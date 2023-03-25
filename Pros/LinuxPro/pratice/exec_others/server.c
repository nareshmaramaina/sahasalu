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
char buf[10]="naresh",buff[10]="jithhu";
mkfifo("fifo3",0777);
fflush(stdout);
if((fd=open("fifo3",O_WRONLY))==-1)
{
perror("open");
exit(0);
}
/*if(fork()==0)
{*/
//printf("enter the data\n");
//scanf("%s",buf);
if(write(fd,buf,20)==-1)
perror("error:");
else 
printf("write success\n");
sleep(2);

write(fd,buff,20);
//perror("error:");
//else 
//printf("write success\n");
//}
//else
//{
//printf("read sucess\n");
//sleep(5);
//read(fd,buf,20);
//printf("%s\n",buf);
//}
while(1);
}
