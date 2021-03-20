#include<header.h>
void sig_handler(int signo)
{
	if (signo == SIGINT)
		printf("\nPlz Don't Use ctrl+c cmd,	To Exit the PcDesk App	 Enter Command --->  #exit#\n");
}

int main (int argc,char *argv[])
{
	FILE *fp;
	char clientid[24]="";
	int PORT=2222;
	int sockfd; 
	int nsockfd; 
	char cmd[256]="";	
	int sizeRstatus=0;
	int n,ret;
	int sin_size; 
	struct sockaddr_in addr_local; /* client addr */
	struct sockaddr_in addr_remote; /* server addr */
	char time[24]="";
	char date[16]="";
	char file[64]="";	
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
	/* Fill the client socket address struct */
	addr_local.sin_family = AF_INET; // Protocol Family
	addr_local.sin_port = htons(PORT); // Port number
	addr_local.sin_addr.s_addr = INADDR_ANY; // AutoFill local address
	bzero(&(addr_local.sin_zero), 8); // Flush the rest of struct

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
	if(listen(sockfd,BACKLOG) == -1)
	{
		fprintf(stderr, "ERROR: Failed to listen Port. (errno = %d)\n", errno);
		close(sockfd);
		exit(1);
	}
	printf ("[Server] Listening the port %d successfully.\n", PORT);

	sin_size = sizeof(struct sockaddr_in);

	/* Wait a connection, and obtain a new socket file despriptor for single connection */
	if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) == -1) 
	{
		fprintf(stderr, "ERROR: Obtaining new Socket Despcritor. (errno = %d)\n", errno);
		exit(1);
	}


	printf("\e[2J\e[H"); // ctrl + l
	printf("Connected ip address:	\033[1;31m %s\n", inet_ntoa(addr_remote.sin_addr));
	printf("\033[0m"); // reset colour

	bzero(clientid, sizeof(clientid));

	ret = wait_for_data(nsockfd);
	if (ret <=0 )
	{
		fprintf(fp,"\nRead failed, some thing wrong with client\n");
		close(sockfd);
		close(nsockfd);
		return -1;
	}
	read(nsockfd, clientid, sizeof(clientid));

	printf("PosDesk Machine Id:	\033[1;31m %s\n",clientid); 

	memset(date,0,sizeof(date));
	memset(time,0,sizeof(time));

	get_time(date,time);

	bzero(cmd, sizeof(cmd));

	if(strstr(clientid,":") != NULL)
		sprintf(clientid,"%c%c%c%c%c%c%c%c%c%c%c%c",clientid[0],clientid[1],clientid[3],clientid[4],clientid[6],clientid[7],clientid[9],clientid[10],clientid[12],clientid[13],clientid[15],clientid[16]);

	sprintf(cmd,"mkdir -p PosDesk_Logs/%s/",date);

	system(cmd);

	sprintf(file,"PosDesk_Logs/%s/%s.log",date,clientid);	

	fp = fopen(file,"a");

	if(fp == NULL)
	{
		fprintf(stdout,"Log File Not created\n");
		return -1;
	}
	fprintf(fp,"\n******* WELCOME PosDesk and PcDesk  Date: [ %s ]\t Time: [ %s ] *******\n", date ,time);

	printf("\033[0m"); // reset colour
	strcpy(pwd,"/root/");
	while(1)
	{
		bzero(cmd, sizeof(cmd));
		bzero(Check_CmD, sizeof(Check_CmD));
		bzero(arg1, sizeof(arg1));

		printf("\033[1;32mroot@visiontek %s$ \033[0m",pwd); 

		n = 0;

		while ((cmd[n++] = getchar()) != '\n');
		cmd[n-1]=0x00;

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

		else if(	( strcmp(Check_CmD,"vi") == 0 ) || (strcmp(Check_CmD,"vim") == 0 ))
		{
			fprintf(stderr,"sorry, vi editor not allowed\n");
			continue;

		}
		else if(strcmp(Check_CmD ,"rm") == 0 )
		{
				char rmd[256];
				sprintf(rmd,"rm_old%s",cmd+2);
				strcpy(cmd,rmd);
		}
		get_time(date,time);

		write(nsockfd, cmd, sizeof(cmd)); 

		//		fprintf(stdout,"\n\nCMD: %s\n",cmd);

		if ( strcmp(cmd,"#exit#") == 0 )
			break;
		// if msg contains "Exit" then server exit and chat ended. 

repeat:		ret = wait_for_data(nsockfd);
		if (ret <= 0 )
		{
			fprintf(fp,"\nTime out, some thing late processing with client\n");
			break;
		}


		if ( read(nsockfd, &sizeRstatus, sizeof(sizeRstatus)) <= 0 )
		{
			fprintf(stderr,"Bytes are Present, but failed to get it\n");
			fprintf(fp,"Bytes are Present, but failed to get it\n");
			break;
		}

		if ( sizeRstatus == 0  )
		{

			if (strcmp(Check_CmD ,"cd") == 0 )
			{
				ret = wait_for_data(nsockfd);
				if (ret <= 0 )
				{
					fprintf(fp,"\nTime out, some thing late processing with client\n");
					break;
				}
				memset(pwd,0,sizeof(pwd));
				if( read(nsockfd,pwd,sizeof(pwd)) <= 0 )
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

		       fprintf(stdout,"Successfully Uploaded to ftp\nDownloadlink: \033[1;31mftp://rnd:rnd123@115.111.229.10/PosDesk_Uploads%s\033[0m\n",arg1+num);
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
			if ( sizeRstatus > 153600 )
			{
				sleep(1);
				//
				//				write(nsockfd,"#exit#", sizeof(cmd)); 
				fprintf(stdout,"Something Went wrong TX / RX \n");
				fprintf(fp,"\n\nTime: [ %s ]\tCommand: [ %s ]\tStatus: [ Something Went wrong TX / RX ]\n",time,cmd);
				continue;
				//				break;
			}	
			fprintf( stdout, "Need TO Receive %d bytes\n",sizeRstatus);
			fprintf(fp,"\n\nTime: [ %s ]\tCommand: [ %s ]\tStatus: [ Success ]\n",time,cmd);
			file_recv_func(nsockfd,sizeRstatus,fp);
		}
		else if ( sizeRstatus == -2)
		{
			fprintf(fp,"\n\nTime: [ %s ] \tCommand: [ %s ]\tStatus: [ Response Morethan 512kb ]\n",time,cmd);
			fprintf(stdout,"Command Resultant bytes are More than 150KB, Use below command to upload\n");
			fprintf(stdout,"\033[1;31m upload %s\033[0m\nAfter Successful Upload you will find same file in Below ftp link\n",arg1);
		      	fprintf(stdout,"PosDesk Uploads ftp link:\033[1;31m ftp://rnd:rnd123@115.111.229.10/PosDesk_Uploads/\033[0m\n");
		}
			
		else if ( sizeRstatus == -3)
		{
			fprintf(stderr,"\033[1;31mProcess is still running\033[0m\n");
			goto repeat;
		}

		fflush(stdout);	

	}	
	printf("Exiting ... Wait for 5 secs\n");
	sleep(5);
	fclose(fp);
	close(nsockfd);
	close(sockfd);
	return 0;
}
