#include<header.h>
int wait_for_data(int sockid)
{
	int bytes,i;
	for(bytes=0,i=1 ; i < 80 * 2 ;i++) 
	{
		ioctl(sockid,FIONREAD,&bytes);
		if(bytes>0)
			return bytes;

		if ( i % 10 == 0 ) 
		printf("\nPlease Wait, Data not avaiable on socket, Retrying ... \n");
		//printf("\nNo Data found to read on socket, Please Wait Retrying ... \n");

		usleep(500000); // Wait for 0.5 sec
	}
	return -1;
}
