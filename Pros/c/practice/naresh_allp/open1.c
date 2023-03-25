#include<stdio.h>
#include<fcntl.h>

int main()
{
int fd=40,i,fd1;
for(i=1;i;)
{
fd=open("grep.c",O_RDONLY);
printf("  1 opening = %d\t fd = %d\n",i++,fd);
if(fd<0)
return -1;
fd1=open("env.c",O_RDONLY);
printf("  2 opening = %d\t fd1 = %d\n",i++,fd1);
if(fd<0)
return -1;

}

close(fd);
close(fd1);

}
