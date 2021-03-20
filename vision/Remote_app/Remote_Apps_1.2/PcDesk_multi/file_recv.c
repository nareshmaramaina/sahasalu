#include<header.h>
void file_recv_func(int sockfd,int size,FILE *fp) 
{
	char recvbuf[LENGTH];	 
	int Total_recved_size =0;
	int secs=0; //sleep secs
	int fr_block_sz = 0;
	fflush(stdout);
	int ret;
	printf("***************************************************************************\n");
	bzero(recvbuf, LENGTH); 
	while(1)
	{

		ret = wait_for_data(sockfd);
		if (ret <= 0 )
		{
			fprintf(stderr,"Read failed, some thing wrong with client\n");
			fprintf(fp,"\nRead failed, some thing wrong with client\n");
			break;
		}

		fr_block_sz = recv(sockfd, recvbuf, LENGTH, 0); 
		Total_recved_size += fr_block_sz;
		recvbuf[fr_block_sz]='\0';
		fprintf(stdout,"%s",recvbuf);	
		fprintf(fp,"%s",recvbuf);
		bzero(recvbuf, LENGTH);
		if (fr_block_sz == 0 || fr_block_sz != LENGTH) 
		{
			if ( size == Total_recved_size)
			{
				printf("\n********************* EXIT SESSION CMD : #exit#  *********************\n");
				break;
			}
			else 
			{

				sleep(secs++);
				if(secs == 5)
				{
				fprintf(stdout,"\nSomething went wrong, Not Received all bytes, Expected to Receive Bytes = %d,Total Received Bytes = %d\n",size,Total_recved_size);
					secs=1;
				}
			}
		}
		fflush(stdout);
	}

	fflush(stdout);
	return;

} 
