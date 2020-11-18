#include<stdio.h>
#include<linux/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>


#define READ 1
#define WRITE 0

int main()
{
	char *file_name = "/dev/char_dev";
	int fd;
	fd = open(file_name,O_RDWR);
	if (fd == -1)
	{
		perror("Error in apps open \n");
		return 0;

	}
	else
		printf("device opened successfully with ret val=%d\n",fd);

	ioctl_set_msg(fd);
	ioctl_get_msg(fd);
	return;
}
int ioctl_set_msg(int fd)
{
	int ret,c;
	ret=ioctl(fd,WRITE,&c);
	if(ret<0)
		printf("unable to set msg\n");
	else
		printf("msg is set successfully with ret value=%d\n",ret);
	return;
}
int ioctl_get_msg(int fd)
{
	int ret,c=0;
	ret=ioctl(fd,READ,&c);
	if(ret<0)
		printf("unable to get msg\n");
	else
		printf("get msg is successfull with ret val=%d\n",ret);
	return;
}

