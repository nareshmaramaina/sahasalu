#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
int fd;
char buff[80];
//FILE *fp=NULL;
if((fd=open("/dev/naresh",O_RDONLY))==-1)
{
printf("opening error at  /dev/naresh\n");
return -1;
}
read(fd,buff,80);
puts(buff);
return 0;
}
