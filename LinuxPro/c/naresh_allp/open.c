#include<stdio.h>
#include<fcntl.h>

int main()
{
char str[]="success";
int fd;
	fun();
	write(50,str,strlen(str));
	fun1();
	fun3();

}
int fun ()
{
	int fd1 ,i;
	for ( i=0;i<900;i++)
	{
	fd1 =open("file1",O_RDONLY);
	if(fd1<0)
		return -1;
	printf(" fd1  = %d\n",fd1);
	}
	close(fd1);
	return fd1; 
}

int fun1 ()
{
	int fd2,i ;
	for ( i=0;i<1000;i++)
	{
	fd2 =open("file2",O_RDONLY);
	if(fd2<0)
		{
	fprintf(stdout,"fun2 failed \n");
		return -1;
		}
	printf(" fd2  = %d\n",fd2);
	}
	return fd2; 
}
int fun3 ()
{
	int fd3;
	fd3 =open("file3",O_RDONLY);
	if(fd3<0)
{
	fprintf(stdout,"fun3 failed \n");
		return -1;
}
	printf(" fd3  = %d\n",fd3);
	return fd3; 
}


