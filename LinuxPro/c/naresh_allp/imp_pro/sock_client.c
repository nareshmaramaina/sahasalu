#include<stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <strings.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


int Receive_File_Functionality(int,char *);

int main(int argc,char *argv[])
{
	int sock_fd=0;
	int ret=0;
	char trx_buf[256]="";	
	char buff[128]="";
	char sbuffer[50]="";
	memset(buff,0x00,128);	
	int rlen=0;
	int ret_len=0;
	
	struct sockaddr_in server_addr,client_addr;

	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd<0)
	{
		fprintf(stderr,"Client Socket Creation Error\n");
		return -1;
	}

	bzero((char *)&server_addr,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(atoi(argv[2]));

	ret=connect(sock_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret<0)
	{
		fprintf(stderr,"Connect to Server Failed\n");
		return -1;
	}

	
	if(argc != 4)
	{
	printf("Usage ./client  serverip portno Filename\n");
	return -1;
	}

	sprintf(sbuffer,"%s",argv[3]);
	ret=send(sock_fd,sbuffer,strlen(sbuffer),0);
        printf("Ret of send is %d\n",ret);
        if(ret<=0)
        {
                printf("sending Bytes to server failed\n");
                close(sock_fd);
                return -1;
        }

	ret_len = recv(sock_fd, buff, 1024, 0);
	printf("Received from server: %s \n",buff);
	if (strncmp(buff, "Does not Exist", strlen("Does not Exist")) == 0)
	{
		printf("File does not exist\n");
		return -1;

	}
	else if (strncmp(buff, "Does Exist", strlen("Does Exist")) == 0)
	{
		printf("File does exist\n");
		Receive_File_Functionality(sock_fd,sbuffer);

	}
	else
		printf("Unknown message\n");

	close(sock_fd);

	return 0;
}

int Receive_File_Functionality(int Sock_Fd,char *Receive_File_Server)
{
	FILE *fp;
	char receive_buff[256]="";
	int read_bytes=0;
	int write_bytes=0;

	fp=fopen(Receive_File_Server,"w");

	if(fp==NULL)
	{
		fprintf(stderr,"Unable to Open the File\n");
		return -1;
	} 

	bzero(receive_buff,256);

	while(read_bytes=recv(Sock_Fd,receive_buff,256,0))
	{

		if(read_bytes<0)
		{
			fprintf(stderr,"Error in Received Bytes\n");
			return -1;
		}

		if(strstr(receive_buff,"END")!=NULL)
		{
			printf("End String Found\n");
		}

	
//		printf("recieve Buffer is %s\n",receive_buff);
		write_bytes=fwrite(receive_buff,sizeof(char),read_bytes,fp);

		printf("Written Bytes:%d\n",write_bytes);

		if(write_bytes == read_bytes)
		break;


		if(write_bytes < read_bytes)
		{
			fprintf(stderr,"Incomplete Writing of the Bytes In File\n");
			return -1;
		}
	}
	
	fclose(fp);

	return 0;
}

