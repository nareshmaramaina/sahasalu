#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>

int main()
{
	int listfd, connfd, retval;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	
	listfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listfd < 0) {
		perror("sock:");
		exit(1);
	}
	/* fill address details */	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	// any configured ip
	servaddr.sin_port = htons(8000);	//port no 8000

	/* assign address to socket */
	retval = bind(listfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (retval < 0) {
		perror("bind:");
		exit(2);
	}
	
	listen(listfd, 5);

	while (1) {
		clilen = sizeof(cliaddr);
		connfd = accept(listfd, (struct sockaddr *)&cliaddr, &clilen);
		printf(" client connected \n");
		printf(" client's port no = %d\n", ntohs(cliaddr.sin_port));
	}
}
