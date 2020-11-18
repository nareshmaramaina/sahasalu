#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/ioctl.h>
//#include "chardev.h"
#define IOCTL_SET_MSG 0x43
//#define IOCTL_GET_MSG 0x45
//char *str="this is visiontek";
int ioctl_set_msg(int fd);
int main()
{
	int fd;
	fd=open("/dev/CHANDANA",O_RDWR);
	if(fd<0)
		printf("unable to open the file\n");
	else
		printf("opened the file\n");
	ioctl_set_msg(fd);
	close(fd);
	//ioctl_get_msg(fd);
	return 0;
}
int ioctl_set_msg(int fd)
{
	int a=5;
	int ret;
	ret=ioctl(fd,0x43,&a);
	printf("return value=%d\n",ret);
	if(ret<0)
		printf("no string printed\n");
	else
		printf("string printed=%d\n",a);
}
