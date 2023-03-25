 #include <sys/types.h>
#include<unistd.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include<stdio.h>
int main()
{
int in,out,g;
int i=0;
char buff[100],buffer[]="&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
out=creat("naresh.c",S_IRWXU);
in=open("fork.c",O_RDWR);
//printf("file opened successfully");
read(in,buff,sizeof(buff));
write(out,buff,sizeof(buff));
dup2(in,out);
write(out,buffer,sizeof(buffer));
//while(buff[i])
//putchar(buff[i++]);
}
