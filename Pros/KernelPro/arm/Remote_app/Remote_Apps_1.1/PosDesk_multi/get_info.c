#include<header.h>
int get_macid(char *macid)
{
	typedef unsigned char UC;
	struct ifreq ifr;
	int fd=0;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name,"eth0", IFNAMSIZ-1);
	if(ioctl(fd,SIOCGIFHWADDR, &ifr) <0)
	{
		close(fd);
		return -1;
	}
	close(fd);

	sprintf(macid,"%02X:%02X:%02X:%02X:%02X:%02X",(UC)ifr.ifr_hwaddr.sa_data[0],(UC)ifr.ifr_hwaddr.sa_data[1],(UC)ifr.ifr_hwaddr.sa_data[2], (UC)ifr.ifr_hwaddr.sa_data[3],	(UC)ifr.ifr_hwaddr.sa_data[4], (UC)ifr.ifr_hwaddr.sa_data[5]);

	return 0;
}
int get_Machineid(char *machineid)
{

	int ret=0;

	FILE *fp=NULL;

	ret = system("fw_printenv machineid | grep machineid=  |cut -c11-20 > /tmp/machineid");

	if(ret != 0 )
		return -1;

	fp = fopen("/tmp/machineid", "r");

	if(fp ==NULL)
	{

		fprintf(stderr,"LIB#Unable To Open The /tmp/machineid\n");
		return -1;

	}

	fscanf(fp,"%s",machineid);

	fclose(fp);

	remove("/tmp/machineid");

	if ( strlen(machineid) != 10 )
		return -1;
	else 
		return 0;

}

