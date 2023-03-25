#include<header.h>
int sockfd; 
int client_sockfd;
int Foreground;
int stop_flag;
void sig_handler(int signo)
{

	stop_flag = 1;
	fprintf(stdout,"\n \033[1;31mPlease wait, Sending stop signal ...\nNote: Output of command will show after sent stop signal \033[0m\n");

}
void alarmHandler(int signo)
{
	close(client_sockfd);
	close(sockfd);

	fprintf(stderr,"\n\033[1;31mClient session expires,  \nFirst command session timeout  60 secs, After onwards it will be 3mins\033[0m\n");
	exit(1);
}

int main (int argc,char *argv[])
{
	FILE *fp;
	int Send_bytes=0;
	int Sent_bytes=0;
	char clientid[24]="";
	int PORT=2222;
	char cmd[256]="";	
	int sizeRstatus=0;
	int Wrong=0;
	int n,ret,in;

	socklen_t sin_size; 
	struct sockaddr_in addr_local; /* client addr */
	struct sockaddr_in addr_remote; /* server addr */
	char time[24]="";
	char date[16]="";
	char file[128]="";	
	char Check_CmD[128],arg1[128];
	char pwd[512]="";

	if(argc == 2)
		PORT=atoi(argv[1]);

	if ( PORT > 65534)
	{
		fprintf(stderr,"Error:argument 2, choose port number is Less than 65535\n");
		return 0;
	}

	/* Get the Socket file descriptor */
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor. (errno = %d)\n", errno);
		exit(1);
	}
	else 
		printf("[Server] Obtaining socket descriptor successfully.\n");

	signal(SIGINT,sig_handler);
	signal(SIGALRM,alarmHandler);
	/* Fill the client socket address struct */
	addr_local.sin_family = AF_INET; // Protocol Family
	addr_local.sin_port = htons(PORT); // Port number
	addr_local.sin_addr.s_addr = INADDR_ANY; // AutoFill local address
	bzero(&(addr_local.sin_zero), 8); // Flush the rest of struct
	/*int yes = 1;
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) 
	{
		perror("setsockopt");
		exit(1);
	}*/

	/* Bind a special Port */
	if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
	{
		fprintf(stderr, "ERROR: Failed to bind Port. (errno = %d)\n", errno);
		close(sockfd);
		exit(1);
	}
	else 
		printf("[Server] Binded tcp port %d in addr 127.0.0.1 sucessfully.\n",PORT);

	/* Listen remote connect/calling */
	if(listen(sockfd,0) == -1)
	{
		fprintf(stderr, "ERROR: Failed to listen Port. (errno = %d)\n", errno);
		close(sockfd);
		exit(1);
	}
	printf ("[Server] Listening the port %d successfully.\n", PORT);

	sin_size = sizeof(struct sockaddr_in);
	/* Wait a connection, and obtain a new socket file despriptor for single connection */

	while(1)
	{

		printf("\e[2J\e[H"); // ctrl + l
		if ( access("Remote_IDs.txt",F_OK) == 0 )
		{
			printf("\nServer serves only below Mentioned Remote IDs\n");
			system("cat -n Remote_IDs.txt");
		}
		printf("\n\033[1;31mWaiting for new incoming connections...,\tOn Port Number = %d\033[0m\n", PORT);
		printf("\nIf You Want  to take particular POS Device ID remote, Please write that Machineid Number in \033[1;31mRemote_IDs.txt\033[0m ( Current working folder)\n");

		printf("Remember	\033[1;31mcntl+c\033[0m - To stop Device process\n		\033[1;31mctrl+\\\033[0m (back slash ) - To Quit current PcDesk process\n"); 
		if ((client_sockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) == -1) 
		{
			fprintf(stderr, "ERROR: Obtaining new Socket Despcritor. (errno = %d)\n", errno);
			close(sockfd);
			exit(1);
		}

		printf("\033[0m"); // reset colour
		printf("\nConnected ip address:	\033[1;31m %s\n", inet_ntoa(addr_remote.sin_addr));
		printf("\033[0m"); // reset colour

		bzero(clientid, sizeof(clientid));


		ret = wait_for_data(client_sockfd);
		if (ret <=0 )
		{
			fprintf(stderr,"\nRead failed, for Clientid  some thing wrong with client\n");
			close(client_sockfd);
			close(sockfd);
			return -1;
		}
		read(client_sockfd, clientid, sizeof(clientid));

		printf("PosDesk Device Id:	\033[1;31m %s\n",clientid); 

		memset(date,0,sizeof(date));
		memset(time,0,sizeof(time));

		get_time(date,time);

		bzero(cmd, sizeof(cmd));


		sprintf(cmd,"mkdir -p PosDesk_Logs/%s/",date);

		system(cmd);

		memset(file,0,sizeof(file));

		sprintf(file,"PosDesk_Logs/%s/%s.log",date,clientid);	

		if ( access(file,F_OK) != 0 )
			fp = fopen(file,"w");

		else 
			fp = fopen(file,"a");

		if(fp == NULL)
		{
			fprintf(stdout," %s Log File Not created\n", file);
			return -1;
		}
		fprintf(fp,"\n******* WELCOME PosDesk and PcDesk  Date: [ %s ]\t Time: [ %s ] *******\n", date ,time);

		printf("\033[0m"); // reset colour
		strcpy(pwd,"/root/");
		in=0;
		ret = Check_Remote_Id(clientid);
		if ( ret != 0 )
		{
			fprintf(stderr,"\"%s\" Client ID Not Matching with Remote_IDS in Remote_IDs.txt file\n",clientid);
			write(client_sockfd,"#busy#", 7);
			fprintf(stdout,"Waiting for 5secs, Removing Session with \"%s\" Client ID",clientid);
			sleep(5);
			close(client_sockfd);
			fclose(fp);
			continue;	
		}	
		else 
		{
			write(client_sockfd,"#OK#", 7);

		}



		ret = wait_for_data(client_sockfd);
		if (ret <= 0 )
		{
			fprintf(fp,"\nTime out, some thing late processing with client\n");
			fclose(fp);
			break;
		}


		if ( read(client_sockfd, &sizeRstatus, sizeof(sizeRstatus)) <= 0 )
		{
			fprintf(stderr,"Bytes are Present, but failed to get it\n");
			fprintf(fp,"Bytes are Present, but failed to get it\n");
			fclose(fp);
			break;
		}

		if ( sizeRstatus != 0  )
		{
			printf("\033[0m"); // reset colour
			printf("\033[1;31m");
			file_recv_func(client_sockfd,sizeRstatus,fp);
			printf("\033[0m"); // reset colour
		}

		while(1)
		{
			bzero(cmd, sizeof(cmd));
			bzero(Check_CmD, sizeof(Check_CmD));
			bzero(arg1, sizeof(arg1));

			printf("\033[1;32m%s@visiontek %s$ \033[0m",clientid,pwd); 

			n = 0;
			if(in++)	
				alarm(3*60); // secs
			else alarm(60); //secs

			while ((cmd[n++] = getchar()) != '\n');
			cmd[n-1]=0x00;

			alarm(0);

			stop_flag = 0;
			Foreground = 0;
			if ( strlen(cmd) == 0 )
				continue;
			else if ( strlen(cmd) > 256 )
			{
				printf("sorry, Maximum command length should be less than 256bytes.\n");
				continue;
			}
			sscanf(cmd,"%s%s",Check_CmD,arg1);


			if (strcmp(Check_CmD ,"clear") == 0 )
			{
				printf("\e[2J\e[H"); // ctrl + l
				continue;
			}

			else if (strcmp(Check_CmD ,"upload") == 0 )
			{
				if( strlen(arg1) == 0 )
				{
					fprintf(stderr,"give upload filename\n");
					continue;
				}	 

			}

			else if(	( strcmp(Check_CmD,"vi") == 0 ) || (strcmp(Check_CmD,"vim") == 0 ) || (strstr(Check_CmD,"devkermit") != NULL)   )
			{
				fprintf(stderr,"sorry, vi/vim editor and devkermit not allowed, Use other methods\n");
				continue;

			}
			else if(strcmp(cmd ,"top") == 0 )
			{
				fprintf(stderr,"\033[1;31mtop -d 1 -n 1 <--- Please Use this command -n for no of times -d for no of secs\033[0m\n");
				continue;
			}
			else if(strcmp(Check_CmD ,"rm") == 0 )
			{
				char rmd[256];
				sprintf(rmd,"rm_old%s",cmd+2);
				strcpy(cmd,rmd);
			}
			get_time(date,time);

			Send_bytes = strlen(cmd);	
			Sent_bytes = write(client_sockfd, cmd, Send_bytes); 

			if(Send_bytes !=  Sent_bytes )
			{
				fprintf(stderr," Need to Send Bytes = %d, but Sent Bytes = %d\n",Send_bytes,Sent_bytes); 
				break;
			}


			//		fprintf(stdout,"\n\nCMD: %s\n",cmd);

			if ( strcmp(cmd,"#exit#") == 0 )
				break;
			// if msg contains "Exit" then server exit and chat ended. 

repeat:		ret = wait_for_data(client_sockfd);
		if (ret <= 0 )
		{
			fprintf(fp,"\nTime out, some thing late processing with client\n");
			break;
		}


		if ( read(client_sockfd, &sizeRstatus, sizeof(sizeRstatus)) <= 0 )
		{
			fprintf(stderr,"Bytes are Present, but failed to get it\n");
			fprintf(fp,"Bytes are Present, but failed to get it\n");
			break;
		}

		if ( sizeRstatus == 0  )
		{

			if (strcmp(Check_CmD ,"cd") == 0 )
			{
				ret = wait_for_data(client_sockfd);
				if (ret <= 0 )
				{
					fprintf(fp,"\nTime out, some thing late processing with client\n");
					break;
				}
				memset(pwd,0,sizeof(pwd));
				if( read(client_sockfd,pwd,sizeof(pwd)) <= 0 )
				{
					fprintf(stderr,"Bytes are Present, but failed to get it\n");
					fprintf(fp,"Bytes are Present, but failed to get it\n");
					break;
				}
				pwd[strlen(pwd)]='\0';
			}
			else if ( strcmp(Check_CmD,"upload") == 0 )
			{
				int num,i;
				for(i=0, num=0;arg1[i];i++)
					if(arg1[i] == '/')
						num=i;

				fprintf(stdout,"Successfully Uploaded to ftp\nDownload from here: \033[1;31mftp://rnd:rnd123@115.111.229.10/PosDesk_Uploads/	\nUploaded %s file may be with different name, PosID_Path_file Ex: .%s_%s\033[0m\n",arg1+num,clientid,arg1+num);
				fprintf(fp,"\n\nTime: [ %s ]\tCommand: [ %s ]\tStatus: [ Success ]\n",time,cmd);
			}
			else if ( strcmp(Check_CmD,"ls") == 0 ) 
				fprintf(stdout,"This is Empty Directory\n");

			else fprintf( stdout, "Command Success \n");
			fprintf(fp,"\n\nTime: [ %s ]\tCommand: [ %s ]\tStatus: [ Success ]\n",time,cmd);
		}
		else if ( sizeRstatus == -1) 
		{
			fprintf(fp,"\n\nTime: [ %s ]\tCommand: [ %s ]\tStatus: [ fail ]\n",time,cmd);
			fprintf( stdout, "Command Failed\n");
		}
		else if ( sizeRstatus > 0 )
		{
			if ( sizeRstatus > 524288  ) // PosDesk Wrong value
			{

				fprintf(stdout,"Something Went wrong TX / RX \n");
				fprintf(fp,"\n\nTime: [ %s ]\tCommand: [ %s ]\tStatus: [ Something Went wrong TX / RX ]\n",time,cmd);
				if(Wrong >= 5 )
					break;
				sleep(++Wrong);
				continue;
			}	
			fprintf( stdout, "Need TO Receive %d bytes\n",sizeRstatus);
			fprintf(fp,"\n\nTime: [ %s ]\tCommand: [ %s ]\tStatus: [ Success ]\n",time,cmd);
			file_recv_func(client_sockfd,sizeRstatus,fp);
		}
		else if ( sizeRstatus == -2) // If size more than 512KB 
		{
			fprintf(fp,"\n\nTime: [ %s ] \tCommand: [ %s ]\tStatus: [ Response Morethan 512kb ]\n",time,cmd);
			fprintf(stdout,"Command Resultant bytes are More than 150KB, Use below command to upload\n");
			fprintf(stdout,"\033[1;31m upload %s\033[0m\nAfter Successful Upload you will find same file in Below ftp link\n",arg1);
			fprintf(stdout,"PosDesk Uploads ftp link:\033[1;31m ftp://rnd:rnd123@115.111.229.10/PosDesk_Uploads/\033[0m\n");
		}

		else if ( sizeRstatus == -3)
		{
			Foreground=1;
			if(stop_flag == 0)
				fprintf(stderr,"\033[1;31mProcess is still running, To stop process, Press cntl+c\033[0m\n");
			//			else if (stop_flag == 1)
			//	sleep(10);	
			write(client_sockfd,&stop_flag,sizeof(stop_flag));
			goto repeat;

		}

		fflush(stdout);	
		}

		printf("Exiting ... \n");
		//sleep(5);
		close(client_sockfd);
		fclose(fp);
	}
	close(sockfd);
	printf("Exiting... Try again\n");
	return -1;
}
