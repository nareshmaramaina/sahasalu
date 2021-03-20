#include<header.h>
int wait_for_data(int sockfd,int timeout)
{
	int bytes,i;
	printf("Timeout secs = %d\n",timeout);
	for(bytes=0,i=0 ; i < timeout * 2 ;i++) 
	{
		ioctl(sockfd,FIONREAD,&bytes);

		if(bytes>0)
			return bytes;

		usleep(500000); // Wait for 0.5 sec
		if(i%10 == 0 )
		printf("No Data Found for read, Retrying..., Foreground_process status = %d Secs completed %d\n",Foreground_process,i/2);
	}
	return -1;
}
