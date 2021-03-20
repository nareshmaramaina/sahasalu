#include<header.h>
int wait_for_data(int sockid)
{
	int bytes,i;
	int ret;
	for(bytes=0,i=0 ; i < 120 * 2 ;i++) 
	{
		ret = ioctl(sockid,FIONREAD,&bytes);

		printf("ioctl ret = %d, bytes = %d\n", ret,bytes);
		if(bytes>0)
			return bytes;

		usleep(500000); // Wait for 0.5 sec
		if(i%10 == 0 )
		printf("No Data Found for read, Retrying...\n");
	}
	return -1;
}
