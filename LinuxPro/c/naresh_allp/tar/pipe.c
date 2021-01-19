#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	char buffer[80],string[]="naresh under a practice sesion";
	int fd[2];	pid_t childpid;
	//childpid=fork();
	pipe(fd);
	if((childpid=fork())==0)
	{
		read(fd[0],buffer,80);
		printf("readed buffer is :%s %d\n",string,getpid());
		exit(0);
	}
	else if (childpid>0)
	{
		write(fd[1],string,sizeof(string)+1);
while(1);
		printf("%d",getpid());
		exit(0);
	}

}
