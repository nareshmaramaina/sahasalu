#include<header.h>

extern char    machineid[24];       
extern char    MACID[24];
extern char Uid[24];
int main(int argc, char *argv[])
{	
	int filesize;
	char	ip_addr[32]="115.111.229.7";
	int	PORT=2222;
	int	ret;
	struct	sockaddr_in remote_addr;
	char	cmd[256]="";
	int	count=0;
	int	TIMEOUT=60;

	if(argc == 2)
	{
		if ( strlen(argv[1]) <= 5)
			PORT=atoi(argv[1]);
		else 
		{
			fprintf(stderr,"Incorrect Port No %s\n",argv[1]);
			return 0;
		}
	}

	else if ( argc == 3)
	{
		if( strlen(argv[1]) > 8 )
		{
			memset(ip_addr,0,sizeof(ip_addr));
			strcpy(ip_addr,argv[1]);
		}
		else 
		{		
			fprintf(stderr,"Error:argument 1, incorrect ip address length\n");
			return 0;
		}
		if ( strlen(argv[2]) <= 5)
			PORT=atoi(argv[2]);
		else 
		{
			fprintf(stderr,"Incorrect Port No %s\n",argv[2]);
			return 0;

		}
	}


	close(0);
	Wait_for_internet();
	

	inet_pton(AF_INET, ip_addr, &remote_addr.sin_addr); 



	/* Get the Socket file descriptor */

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
		exit(1);
	}
	if ( PORT > 65534)
	{
		fprintf(stderr,"Error:argument 2, choose port number is Less than 65535\n");
		return 0;
	}
	fprintf(stdout,"Connecting ... port no = %d\n",PORT);
	/* Fill the socket address struct */
	remote_addr.sin_family = AF_INET; 
	remote_addr.sin_port = htons(PORT); 

	bzero(&(remote_addr.sin_zero), 8);

	/* Try to connect the remote */
	if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
	{
		fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
		exit(1);
	}
	else 
		printf("[Client] Connected to server at port %d...ok!\n", PORT);


	DevInfo();

	if(strlen(machineid) == 10 )
		write(sockfd, machineid,24);
	else if ( strlen(MACID) > 11)  
		write(sockfd, MACID,24);
	else 
		write(sockfd,Uid,24);

	ret = wait_for_data(sockfd,40);

	if (ret <= 0 )
	{
		fprintf(stdout,"Waiting for Acknowlwgment Server May Busy\n");
		close (sockfd);
		return -1;
	}
	if (  read(sockfd, cmd, 7 ) <= 0 )
	{
		fprintf(stdout,"Bytes are Ready but Reading Bytes are failed\n");
		close (sockfd);
		return -1;
	}
	printf("From Server :%s\n", cmd);


	if ((strcmp(cmd, "#OK#")) != 0)
	{
		close (sockfd);
		printf("OK Acknowlegment Failed\n");
		return -1;
	}
	else 
		fprintf(stdout," Acknowledment Recevied Success %s \n",cmd);



	filesize = size_of_file("/tmp/DevInfo");
	if (filesize > 524288  ) // if greater than 512KB
	{
		fprintf(stdout,"************ %d  size \n",filesize);
		filesize = -2;
	}

	fprintf(stdout," Sending filesize %d\n",filesize);
	write(sockfd,&filesize,sizeof(filesize));

	if (filesize > 0 )
		file_send_func(sockfd,"/tmp/DevInfo");



	chdir("/root/");
	signal(SIGALRM, alarmHandler);

	while(1)
	{
		bzero(cmd, sizeof(cmd)); 

		if(count)
		{
			TIMEOUT=3*60; //3mins 
			ret = wait_for_data(sockfd,TIMEOUT); //3 mins  wait for cmd to enter
		}

		else
			ret = wait_for_data(sockfd,TIMEOUT);

		if (ret <= 0 )
		{
			fprintf(stdout,"Reading Bytes failed, Server Left or something went wrong\n"); 
			break;
		}
		if (  read(sockfd, cmd, sizeof(cmd)) <= 0 )
		{
			fprintf(stdout,"Bytes are Ready but Reading Bytes are failed\n"); 
			break;
		}
		printf("From Server :%s\n", cmd); 


		if ((strcmp(cmd, "#exit#")) == 0)
		{	
			close (sockfd);
			printf("Successfully Exiting...\n");
			return 0;	
		}
		else if ((strcmp(cmd, "#busy#")) == 0)
		{	
			close (sockfd);
			printf("Server Busy  Exiting...\n");
			return -1;	
		}


		ret = check_cmd(cmd);

		if ( ret > 0)	
			file_send_func(sockfd,"/tmp/.cmd_buff.log");

		printf("Command count = %d\n",++count); // Should not remove this 
		sleep(1);
	}

	close (sockfd);
	return -1;

}
