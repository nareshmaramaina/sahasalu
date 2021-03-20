#include<header.h>
int main(int argc, char *argv[])
{
	char	ip_addr[32]="115.111.229.7";
	int	PORT=2222;
	int	ret;
	char	machineid[24]="";	
	struct	sockaddr_in remote_addr;
	char	cmd[256]="";
	char	macid[24];
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









	bzero(machineid, sizeof(machineid)); 
	bzero(macid, sizeof(macid)); 

	ret = get_Machineid(machineid);
	if ( ret == 0)
		write(sockfd, machineid,24);

	else 
	{
		get_macid(macid);
		if (strlen(macid) == 0)
			strcpy(macid,"ERROR");
		write(sockfd, macid,24);

	}
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
			return 0;	
		}


		ret = check_cmd(cmd);

		if ( ret > 0)	
			file_send_func(sockfd);

		printf("Command count = %d\n",++count); // Should not remove this 
		sleep(1);
	}

	close (sockfd);
	return -1;

}
