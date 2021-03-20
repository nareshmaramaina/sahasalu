#include<header.h>
void Wait_for_internet(void)
{
	int ret;
	while(1)
	{
		ret = hostname_to_ip("google.co.in");
		if (ret == 0)
		{
			puts("Connection Avaliable");
			return;
		}
		else
		{
			puts("No internet Found");
		}
		sleep(10);
	}
	return;
}

int hostname_to_ip(char *host)
{
	int sockfd;  
	struct hostent *he;
	struct sockaddr_in their_addr;

	res_init();

	if ((he=gethostbyname(host)) == NULL) {  
		herror("gethostbyname");
		return -1;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return -1;
	}

	their_addr.sin_family = AF_INET;      /* host byte order */
	their_addr.sin_port = htons(80);    /* short, network byte order */
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(their_addr.sin_zero), 8);     /* zero the rest of the struct */

	if (connect(sockfd, (struct sockaddr *)&their_addr, \
				sizeof(struct sockaddr)) == -1) {
		perror("connect");
		close(sockfd);
		return -1;
	}
	close(sockfd);
	return 0;

}
