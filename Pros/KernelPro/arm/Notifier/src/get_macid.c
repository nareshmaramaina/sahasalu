#include<header.h>
int get_macid(char *mac)
{
	struct ifreq ifr;
	int fd_anlg=0;
	fd_anlg=socket(AF_INET,SOCK_DGRAM,0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
	if(ioctl(fd_anlg, SIOCGIFHWADDR, &ifr) < 0)
	{
		close(fd_anlg);
		fprintf(stderr,"get_macid failed\n");
		return -1;
	}
	close(fd_anlg);
	memset(mac, 0, sizeof(mac));
	sprintf(mac,"%02X:%02X:%02X:%02X:%02X:%02X",(unsigned char)ifr.ifr_hwaddr.sa_data[0],
			(unsigned char)ifr.ifr_hwaddr.sa_data[1],
			(unsigned char)ifr.ifr_hwaddr.sa_data[2], (unsigned char)ifr.ifr_hwaddr.sa_data[3],
			(unsigned char)ifr.ifr_hwaddr.sa_data[4], (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
	return 0;
}

