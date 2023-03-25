#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd;
	char buf[30];
	fd = open("./abc", O_RDWR);
	getchar();
	printf(" %d \n",read(fd, buf , 20));
	close(fd);
	exit(0);
}
	
