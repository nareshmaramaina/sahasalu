#include <stdio.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	char interface[99];
	Get_interface_name(interface);
	
	if ( strcmp(interface,"ppp0") == 0 )


}

int Get_interface_name(char *interface)
{
	char ip[99], hw[99], flags[99], mac[99], mask[99], dev[99]="", dummy[99]="";

	FILE *fp = fopen("/proc/net/arp", "r");
	if ( fp == NULL )
	{
		fprintf(stderr," /proc/net/arp file not found \n");
		return -1;
	}
	fgets(dummy, 99, fp); //header line

	fscanf(fp, "%s %s %s %s %s %s\n", ip, hw, flags, mac, mask, dev); 
	strcpy(interface,dev);	

	fclose(fp);

	return 0;
}
