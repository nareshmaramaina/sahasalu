#include <stdio.h>
#include <fcntl.h>
#include <string.h>

//    #include "header.h"
#define IOCTL_CMD 0x001

int main()
{
	int ret,fd;
	char * msg = "visiontek";
char *filename="/dev/mymod1";
	fd = open(filename, O_RDWR);
if(fd<0)
	printf("device cannot open ret val=%d",fd);
	ret=ioctl(fd, IOCTL_CMD, msg);
	printf("return value=%d\n",ret);
	if(ret>=0)
		printf("ioctl executed\n");
	close(fd);
	return 0;
}

