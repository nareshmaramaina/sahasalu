
/* Example showing how to implement udp/ip client.
Version: 1.0
Author : Team -C
*/
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <netinet/in.h>
# include <linux/errqueue.h>

main()
{
struct sock_extended_err sockerr;
int len;
struct msghdr mymsg;
len=sizeof(struct sock_extended_err);
char *serv_ip = "127.0.0.1";
char *msg = "abcdefghijklmno";
int sockfd,ret_val;
socklen_t addr_len;
struct sockaddr_in servaddr;
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if(sockfd <0 ){
	perror("error:");
	exit(1);
}
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(8000);
inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);
addr_len = sizeof(struct sockaddr_in);
//send data to the server socket, need not connect to server socket.
setsockopt(sockfd,IPPROTO_IP,IP_RECVERR,&sockerr,len);

ret_val = sendto(sockfd,msg,strlen(msg),0,(struct sockaddr *)&servaddr,addr_len);
printf(" ret val of sendto = %d\n",ret_val);
recvmsg(sockfd,&mymsg,MSG_ERRQUEUE);
close(sockfd);
}
