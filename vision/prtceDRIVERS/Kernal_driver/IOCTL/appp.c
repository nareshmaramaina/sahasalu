#include<stdio.h>
#include<linux/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>


#define READ1 2 
#define WRITE1 3 
	unsigned char msg[10]="visiontek";
int main()
{
	char *file_name = "/dev/CHANDU";
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
	int ret;
	ret=ioctl(fd,WRITE1,msg);
	if(ret<0)
		printf("unable to set msg\n");
	else
		printf("msg is set successfully with ret value=%d %s\n",ret,msg);
	return;
}
int ioctl_get_msg(int fd)
{
	int ret;
	ret=ioctl(fd,READ1,msg);
	if(ret<0)
		printf("unable to get msg\n");
	else
		printf("get msg is successfull with ret val=%d %s\n",ret,msg);
	return;
}

