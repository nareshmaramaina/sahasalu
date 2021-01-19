#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<error.h>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
static char buf[100];
int i,j;
printf("%u\n",getpid());
while(1)
{
i=open("fifo",O_RDONLY);
	if(read(i,buf,100)!=-1)
	{
		printf(" msg: %s",buf);
	}
close(i);

}
}
