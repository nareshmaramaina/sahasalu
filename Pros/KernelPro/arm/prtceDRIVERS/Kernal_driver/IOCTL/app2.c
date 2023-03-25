#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define IOCTL_GET_MSG _IOR('s',0,char *)
#define IOCTL_SET_MSG _IOW('s',1,char *)

int main()
{
	int fd=0,ret,ch=0,val=0;

	fd=open("/dev/ioc_dev",O_RDONLY);
		printf("return value for file open=%d\n",fd);

	if(fd<0)
		fprintf(stderr,"unable to open the file\n");
	else{
		fprintf(stdout,"opened the file\n");
		printf("enter any number(0-1)\n");
		scanf("%d\n",ret);
		switch(0){
			case 0:
				 ch=100;
					ret=ioctl(fd,IOCTL_GET_MSG,&ch);
					if(ret<0)
						printf("unable to get message\n");
					else
						printf("this is ioctl set message%d\n",&ch);
					break;
			case 1:
					
					 val=15;
						ret=ioctl(fd,IOCTL_SET_MSG,&val);
						if(ret<0)
							printf("unable to set the message\n");
						else
							printf("this is ioctl set message\n");
					

					break;
		}close(fd);
		return 0;
	}}

