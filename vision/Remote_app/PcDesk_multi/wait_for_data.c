#include<header.h>
extern int Foreground;
extern int stop_flag;
int wait_for_data(int sockid)
{
	int bytes,i;
	int timeout;
	static int in=0;

	if(in++)
		timeout= 70*2; //80 secs
	else timeout=62*2; //secs

	for(bytes=0,i=1 ; i < timeout ;i++) 
	{
		ioctl(sockid,FIONREAD,&bytes);
		if(bytes>0)
			return bytes;

		if ( stop_flag != 1 && i % 20 == 0 ) 
		{
			if(Foreground == 1 )
				printf("\nPlease Wait %d secs, Data not avaiable on socket, Retrying ...\n",( (timeout/2) - (i/2) - 30 )  );

			else printf("\nPlease Wait %d secs, Data not avaiable on socket, Retrying ...\n",( (timeout/2) - (i/2) ) );

		}
		else if(stop_flag == 1 && i % 20 == 0)
			fprintf(stdout,"\033[1;31mProcessing Please wait %d secs\033[0m\n", ( (timeout/2) - (i/2) - 30 ) );
		usleep(500000); // Wait for 0.5 sec
	}
	return -1;
}
