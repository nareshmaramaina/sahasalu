#include<header.h>

int Foreground_process;
int sockfd; 
static void alarmHandler(int signo)
{	
	int	ret ;
	if ( Foreground_process == 0)
	{
		ret = -3;
		fprintf(stderr,"Still system call is running, Acknowledgment is sending\n");
		write(sockfd,&ret,sizeof(ret));
			alarm(60);
	}

	printf("**** Alarm Exiting*****\n");

}
int main(int argc, char *argv[])
{
	const char* fs_name = "/tmp/.cmd_buff.log";
	char ip_addr[32]="115.111.229.7";
	int PORT=2222;
	int ret=1;
	char machineid[24]="";	
	struct sockaddr_in remote_addr;
	char cmd_buff[256]="";
	char Upload_cmd_buff[512]="";
	char cmd[160]="";

	int filesize = 0;
	char arg1[128];
	char macid[24];
	char Check_CmD[128];
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
	char cwd[512];
	chdir("/root/");
	signal(SIGALRM, alarmHandler);
	while(1)
	{
		bzero(cmd_buff, sizeof(cmd_buff)); 
		bzero(Check_CmD,sizeof(Check_CmD));
		bzero(arg1, sizeof(arg1));

		ret = wait_for_data(sockfd);
		if (ret <= 0 )
		{
			fprintf(stdout,"Reading Bytes failed, Server Left or something went wrong\n"); 
			break;
		}
		if (  read(sockfd, cmd_buff, sizeof(cmd_buff)) <= 0 )
		{
			fprintf(stdout,"Bytes are Ready but Reading Bytes are failed\n"); 
			break;
		}
		printf("From Server :%s\n", cmd_buff); 


		if ((strcmp(cmd_buff, "#exit#")) == 0)
		{	
			close (sockfd);
			printf("Successfully Exiting...\n");
			return 0;	
		}
		sscanf(cmd_buff,"%s%s",Check_CmD,arg1);

		if (strcmp(Check_CmD ,"upload") == 0 && (  strlen(arg1) != 0 ) )
		{


			ret =  access(arg1,F_OK); // arg1 is filename with path


			if ( ret == 0 )
			{
				memset(Upload_cmd_buff,0x00,sizeof(Upload_cmd_buff));

				sprintf(Upload_cmd_buff,"curl -s -u rnd:rnd123 -T    %s  ftp://115.111.229.10/PosDesk_Uploads/  &> /dev/null",arg1);

				puts(Upload_cmd_buff);

				ret = system(Upload_cmd_buff);

				if ( ret != 0)
					ret = -1; 

			}

			else ret = -1;

			write(sockfd,&ret,sizeof(ret));

		}


		else if (strcmp(Check_CmD ,"cd") == 0  )
		{
			if( strlen(arg1) == 0 )
				strcpy(arg1,"/root/");

			ret = chdir(arg1);
			if ( ret != 0 )
				ret =-1;

			printf("ret = %d path = %s\n",ret,arg1);
			write(sockfd,&ret,sizeof(ret));

			if ( ret == 0 )
			{
				memset(cwd,0,sizeof(cwd));
				getcwd(cwd, sizeof(cwd));
				fprintf(stdout,"CWD : %s \n",cwd);
				write(sockfd,cwd,strlen(cwd));

			}	
		}


		else if (strlen(cmd_buff) > 0 )
		{
			bzero(cmd,sizeof(cmd));

			if (( strstr(cmd_buff,">")  == NULL)  &&  (strstr(cmd_buff,">>")  == NULL) && (strstr(cmd_buff,"&")  == NULL) )
				sprintf(cmd,"%s > %s 2>&1",cmd_buff,fs_name);

			else strcpy(cmd,cmd_buff);

			remove(fs_name);

			alarm(60);
			Foreground_process=0;

			ret = system(cmd);

			Foreground_process=1;


			filesize = size_of_file(fs_name);

			if (filesize > 524288  ) // if greater than 512KB
			{	
				fprintf(stdout,"************ %d  size \n",filesize);
				filesize = -2;
			}

			if ( ret != 0 && filesize == 0 )
			{	
				fprintf(stdout,"Command Failed, ret = %d\n",ret);
				filesize = -1; //Fail without any message
			}

			else 
				fprintf(stdout,"Command Success\n");


			fprintf(stdout," Sending filesize %d\n",filesize);
			write(sockfd,&filesize,sizeof(filesize));

			if ( filesize > 0)	
				file_send_func(sockfd);
		}
		sleep(1);
	}

	close (sockfd);
	return -1;

}
