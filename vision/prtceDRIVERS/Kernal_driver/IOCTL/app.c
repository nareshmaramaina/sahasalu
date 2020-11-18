#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include<linux/ioctl.h>

typedef struct {
	int rollno;
	char *name;
}variable;



#define GET_VARIABLES _IOR('c' ,1, variable *)
#define SET_VARIABLES _IOW('c',2, variable *)
#define CLR_VARIABLES  _IO('c',3)

int main(int argc, char *argv[])
{
	int fd,select;
	char *filename="/dev/DEVICE0";
	printf("file name=%s",filename);
	fd=open(filename,O_RDWR);
	if(fd<0)
		printf("cannot open the file\n");
	else
		printf("file opened successfully\n");


	select=atoi(argv[1]);
	switch (select)
	{

		case 1:
			get_variables(fd);
			break;
		case 2:
			set_variables(fd);
			break;
		case 3:
			clr_variables(fd);
			break;
		default:
			break;
	}
	close(fd);
	return 0;
}
int get_variables(fd)
{
	variable c;

	int ret;
	ret=ioctl(fd,GET_VARIABLES,&c);
	if(ret<0)
		printf("unable to get variables\n");
	else
	{
		printf("able to get variables\n");
		printf("roll no=%d\n",c.rollno);
		printf("name=%s\n",c.name);
	}
	return 0;
}

int set_variables(fd)
{
	variable c;
	int ret;

/*printf("enter the number\n");
scanf("%d\n",q.rollno);*/

	ret=ioctl(fd,SET_VARIABLES,&c);
	if(ret<0)
		printf("unable to set variables\n");
	else
		printf("able to set variables\n");
	return 0;
}


int clr_variables(fd)
{
       variable c;
	int ret,i;
	ret=ioctl(fd,CLR_VARIABLES,&c);
	if(ret<0)
		printf("unable to clear variables\n");
	else
		printf("able to clr variables\n");
	return 0;
}


