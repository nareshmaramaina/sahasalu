#include<header.h>
int wait_for_data(int sockid)
{
	extern int stop_flag;
	int bytes,i;
	int timeout;
	static int in=0;

	if(in++)
		timeout= 80*2; //80 secs
	else timeout=60; //secs
	int count=60;

	for(bytes=0,i=1 ; i < timeout ;i++) 
	{
		ioctl(sockid,FIONREAD,&bytes);
		if(bytes>0)
			return bytes;

		if(stop_flag == 0 )
		{
			if ( i % 20 == 0 ) 
				printf("\nPlease Wait, Data not avaiable on socket, Retrying ... Completed Secs = %d \n",i/2);

		}
		else if(stop_flag == 1 )
		{
			if( count > 0  && (count % 2 == 0) )
			{
				fprintf(stdout,"\033[1;31mProcessing Please wait %d secs\033[0m\n",count/2);
				count--;
			}
			else if ( i % 20 == 0 ) 
				printf("\nPlease Wait, Data not avaiable on socket, Retrying ... Completed Secs = %d \n",i/2);
		}
		usleep(500000); // Wait for 0.5 sec
	}
	return -1;
}
