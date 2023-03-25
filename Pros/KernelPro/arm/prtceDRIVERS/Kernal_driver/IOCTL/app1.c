#include<stdio.h>
#include<linux/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
unsigned char *s;

#define 	IOCTL_GET_MSG	 	_IO ('s',1 )
#define  	IOCTL_SET_MSG		_IOR('s',2,char *)
#define 	IOCTL_CLR_MSG		_IOW('s',3,char *)

int main(int argc , char *argv[])
{
	char *file_name ="/dev/ioctl1";
	int fd,option =0;
	option = atoi(argv[1]);
	printf("option =%d\n",option);
	fd=open(file_name,O_RDWR);
	{
		if(fd == -1)
		{
			printf("cannot open the file");
			return -1;
		}
		else
		{
			int ret ,c;
			switch (option)
			{
			case 1:
					ret=ioctl(fd,IOCTL_GET_MSG,&c);
					if(ret<0)
					{
						printf("ioctl get msg failure\n");
						return -1;
					}
					else
					{
						printf("ioctl get msg successfull%d C Val=%d\n",ret,c);
						return 0;
					}
					break;
			case 2:
					c=10;
					ret=ioctl(fd,IOCTL_SET_MSG,&c);

                        		if(ret<0)
					{
						printf("ioctl get msg failure\n");
						return -1;
					}
					else
					{

						printf("ioctl get msg successfull%d C Val=%d\n\n",ret);
						return 0;
					}
					break;

			case 3:
					c=0;

		        		ret=ioctl(fd,IOCTL_CLR_MSG,&c);

                       			 if(ret<0)
					 {
						 printf("ioctl get msg failure\n");
						 return -1;
					 }
					 else
					 {
						 printf("ioctl get msg successfull%d C Val %d\n",ret,c);
						 return 0;
					 }

				}
}}
}
