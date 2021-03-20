#include<header.h>
void file_send_func(int sockfd , char *fs_name)
{
//	const char* fs_name = "/tmp/.cmd_buff.log";
	char sdbuf[LENGTH]; 
	printf("Sending %s file to the Server...\n", fs_name);
	FILE *fs = fopen(fs_name, "r");
	int fs_block_sz=0;
	if(fs == NULL)
	{
		printf("ERROR: File %s not found.\n", fs_name);
		return;
	}
	bzero(sdbuf, LENGTH); 
	while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) > 0)
	{
		sdbuf[fs_block_sz]='\0';
		puts(sdbuf);
		if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
		{
			fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
			break;
		}
//		printf(" %sSIZE = %d\n",sdbuf,fs_block_sz);
		bzero(sdbuf, LENGTH);
	}

	fprintf(stdout,"Successfully Sent\n");

	return;
}


