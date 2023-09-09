#include<stdio.h>
#include <sys/types.h>  //For Socket Creation and Bind        
#include <sys/socket.h> // For Socket Creation and Bind
#include <strings.h> //For bzero 
#include <netinet/in.h> //For Bind and Connect
#include <unistd.h> //For Fork
#include <sys/sendfile.h> //For Send_File
#include <sys/types.h>//For Open SystemCall
#include <sys/stat.h>//For Open SystemCall
#include <fcntl.h>//For Open SystemCall
#include <string.h>
#include <stdlib.h>


#define BACKLOG		5 //Handles upto 5 Clients

int Send_File_Functionality(int,char *);

int main (int argc,char *argv[])
{
	int sock_fd=0;
	int ret=0;
	int accept_sockfd=0;
	int client_len=0;
	char trx_buf[256]="";
	char buffer[50]="";
	char file_path[50]="";
	char buff[128]="";

	int wlen=0;
	int ret_len=0;
	memset(buffer,0x00,50);
	memset(file_path,0x00,50);
	memset(buff,0x00,128);
	pid_t child_pid;

	struct sockaddr_in server_addr,client_addr;

	sock_fd=socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd<0)
	{
		fprintf(stderr,"Server Socket Creation Error\n");
		return -1;
	}

	bzero((char *)&server_addr,sizeof(server_addr));

	if (argc!=2)
	{
		fprintf(stdout, "./server PortNumber");
		return -1;	

	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//server_addr.sin_addr.s_addr = inet_addr("115.111.229.7");

	server_addr.sin_port = htons(atoi(argv[1]));

	ret=bind(sock_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret<0)
	{
		fprintf(stderr,"Bind Failed\n");
		return -1;
	}	

	ret=listen(sock_fd,BACKLOG);
	if(ret<0)
	{
		fprintf(stderr,"Listen Error\n");
		return -1;
	}	
	fprintf(stdout,"Server in Listening Mode....\n");

	client_len=sizeof(client_addr);
	while(1)
	{

		accept_sockfd=accept(sock_fd,(struct sockaddr *)&client_addr,&client_len);
		if(accept_sockfd<0)
		{	
			fprintf(stderr,"Accepting the Client Connection Failed\n");
			return -1;
		}	

		child_pid=fork();
		if(child_pid < 0)
		{
			fprintf(stderr,"Error in Fork Creation\n");
			return -1;
		}

		if(child_pid == 0)
		{
			fprintf(stdout,"Executing the Client Process\n");

			close(sock_fd);

			ret=recv(accept_sockfd,buffer,50,0);
			if(ret<0)
			{
				fprintf(stdout,"filename Received Zero Bytes\n");	
				return -1;
			}

			printf("%s\n",buffer);
			FILE *fp;
			int ret=0;
			sprintf(file_path,"/root/%s",buffer);		
			ret=access(file_path,F_OK);
			if(ret == 0)
			{
				fp = fopen(file_path,"r");
				if(fp == NULL)
				{
					fprintf(stdout,"file open error\n");
					strncpy(buff, "Does not Exist", strlen("Does Not Exist"));

				}	
				else {
					printf ( "file exists!\n" );
					strncpy(buff, "Does Exist", strlen("Does Exist"));
				}
				ret_len = send(accept_sockfd,buff,strlen(buff),0);

				if(ret_len<0)
				{
					fprintf(stderr,"send_to failed %d\n",ret_len);
					printf("ret len is %d\n",ret_len);
					return -1;
				}		



				Send_File_Functionality(accept_sockfd,file_path);
				fclose(fp);	
			}

			return 0;
		}
		else
		{
			close(accept_sockfd);
		}	
	}
	return 0;
}

int Send_File_Functionality(int Sock_Fd,char *File_to_Send)
{
	int fd=0;	
	off_t offset1;	
	struct stat Stat_Buf;	
	int send_bytes=0;	
	char End_Buf[4]="END";
	int wr_ret=0;

	fd=open(File_to_Send,O_RDONLY); 	
	if(fd == 0)
	{
		fprintf(stderr,"Unable to Open the File\n");
		return -1;
	}     		
	fprintf(stdout,"Opened the Sending File\n");	

	offset1=0; 

	fstat(fd,&Stat_Buf);	 		


	send_bytes=sendfile(Sock_Fd,fd,&offset1,Stat_Buf.st_size); 	
	//send_bytes=sendfile(Sock_Fd,fd,&offset1,Stat_Buf.st_size); 	
	printf("Send_Bytes:%d\n",send_bytes);

	if(send_bytes < 0)
	{
		fprintf(stderr,"Error in Copying the Data between Two File Descriptors\n");	
		return -1;
	}			
	fprintf(stdout,"Copying the Data Between Two File Descriptors Success\n");	

	if(send_bytes != Stat_Buf.st_size)
	{
		fprintf(stderr,"Incomplete Sending of File\n");
		return -1;
	}	
	fprintf(stdout,"Sending File Completed\n");

	wr_ret=sendto(Sock_Fd,End_Buf,3,0,NULL,0);
	if(wr_ret < 0)
	{
		fprintf(stderr,"End String Send Error\n"); 
		return -1;
	}
	fprintf(stdout,"End String Send Success\n");
	close(fd);
	return 0;
}

