#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

int main(void)
{
	int fd;
	struct if_nameindex *curif, *ifs;
	struct ifreq req;

	if((fd = socket(PF_INET, SOCK_DGRAM, 0)) != -1) {
		ifs = if_nameindex();
		if(ifs) {
			for(curif = ifs; curif && curif->if_name; curif++) {
				strncpy(req.ifr_name, curif->if_name, IFNAMSIZ);
				req.ifr_name[IFNAMSIZ] = 0;
				if (ioctl(fd, SIOCGIFADDR, &req) < 0)
					perror("ioctl"); //Getting Error here
				else
					printf("%s: [%s]\n", curif->if_name,
							inet_ntoa(((struct sockaddr_in*) &req.ifr_addr)->sin_addr));
			}
			if_freenameindex(ifs);
			if(close(fd)!=0)
				perror("close");
		} else
			perror("if_nameindex");
	} else
		perror("socket");
	return 0;
}
