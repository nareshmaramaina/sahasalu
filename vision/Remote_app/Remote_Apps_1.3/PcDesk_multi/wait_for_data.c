#include<header.h>
extern int Foreground;
extern int stop_flag;
int wait_for_data(int sockid)
{
	int bytes,i;
	int timeout;
	static int in=0;

	if(in++ == 0 )
		timeout=42*2;
	else if ( in == 1 )
		timeout= 62*2; //80 secs

	else timeout= 80*2; //80 secs

	for(bytes=0,i=1 ; i < timeout ;i++) 
	{
		ioctl(sockid,FIONREAD,&bytes);
		if(bytes>0)
			return bytes;

		if ( stop_flag != 1 && i % 20 == 0 ) 
			 printf("\nPlease Wait %d secs, Data not avaiable on socket, Retrying ...\n",( (timeout/2) - (i/2) ) );

		else if(stop_flag == 1 && i % 20 == 0)
			fprintf(stdout,"\033[1;31mProcessing Please wait ... some secs, (Max 80secs)\033[0m\n");
		usleep(500000); // Wait for 0.5 sec
	}
	return -1;
}
