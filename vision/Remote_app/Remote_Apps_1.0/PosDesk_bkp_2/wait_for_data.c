#include<header.h>
int wait_for_data(int sockid)
{
	int bytes,i;
	for(bytes=0,i=0 ; i < 120 * 2 ;i++) 
	{
		ioctl(sockid,FIONREAD,&bytes);

		if(bytes>0)
			return bytes;

		usleep(500000); // Wait for 0.5 sec
		if(i%10 == 0 )
		printf("No Data Found for read, Retrying...\n");
	}
	return -1;
}
