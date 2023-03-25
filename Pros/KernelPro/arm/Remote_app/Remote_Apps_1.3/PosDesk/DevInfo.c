#include<header.h>
int get_app_details();
void get_project_name(char *name);
void get_uid(char *uid);
int get_Machineid(char *);
int get_macid(char *);
void Update_UpldDate();
void get_date(int *day,int *month,int *year);
int rootfs_details(char *rootfs);
int 	kernel_details(char *kernel);
int 	bootloader_details(char *u_boot);
int patch_ver(char *version);

char machineid[24];
char Uid[24];
char MACID[24];
char A_type[32];
char A_ver[10];
int DevInfo()
{
	FILE *fp=NULL;
	char macid[24];
	char Project_name[22];
	char Upld_file[64];
	char u_boot[80],kernel[80],rootfs[80];
	char version[80];

	memset(Project_name,0,sizeof(Project_name));

	get_project_name(Project_name);

	if(strlen(Project_name) == 0 )
		strcpy(Project_name,"ERROR");

	memset(Uid,0,sizeof(Uid));

	get_uid(Uid);

	if(strlen(Uid) == 0 )
		strcpy(Uid,"ERROR");


	get_app_details();

	if(strlen(A_type) == 0 )
		strcpy(A_type,"ERROR");

	if(strlen(A_ver) == 0 )
		strcpy(A_ver,"ERROR");


	memset(macid, 0, sizeof(macid));

	get_macid(macid);

	if(strlen(macid) == 0 )
		strcpy(macid,"ERROR");


	memset(machineid,0,sizeof(machineid));

	get_Machineid(machineid);



	memset(u_boot,0,sizeof(u_boot));
	memset(kernel,0,sizeof(kernel));
	memset(rootfs,0,sizeof(rootfs));
	memset(version,0,sizeof(version));
	rootfs_details(rootfs);
	kernel_details(kernel);
	bootloader_details(u_boot);
	patch_ver(version);



	fp = fopen("/tmp/DevInfo","w");

	if ( fp == NULL)
	{
		fprintf(stderr,"open error %s\n",Upld_file);
		return -1;
	}	

	if ( strlen(machineid) != 10 )
	{
	fprintf(fp,"ProjectName: %s\nMachineid: %s (ERROR)\nMacid: %s\nUid: %s\nAppType: %s\nAppVersion: %s\nU-boot: %s\nKernel: %s\nRootfs: %s\nFirmwareVersion: %s\n",Project_name,machineid,macid,Uid,A_type,A_ver,u_boot,kernel,rootfs,version);

	}
	else 
	fprintf(fp,"ProjectName: %s\nMachineid: %s\nMacid: %s\nUid: %s\nAppType: %s\nAppVersion: %s\nU-boot: %s\nKernel: %s\nRootfs: %s\nFirmwareVersion: %s\n",Project_name,machineid,macid,Uid,A_type,A_ver,u_boot,kernel,rootfs,version);

	fprintf(stdout,"ProjectName:%s\nMachineid:%s\nMacid:%s\nUid:%s\nAppType:%s\nAppVersion:%s\nU-boot:%s\nKernel:%s\nRootfs:%s\nFirmwareVersion:%s\n",Project_name,machineid,macid,Uid,A_type,A_ver,u_boot,kernel,rootfs,version);

	fclose(fp);
	
	return 0;
}


int  get_app_details()
{

	FILE *fp=NULL;

	char buff[128];

	fp = fopen("/mnt/sysuser/app_ver","r");

	if (fp==NULL)
	{
		fprintf(stderr,"Application Version File open error\n");
		return -1;
	}

	memset(buff,0x00,sizeof(buff));

	while( fscanf(fp, "%s",buff) > 0 )
	{

		if ( strstr(buff,"APP_TYPE:") != NULL)
			strcpy(	A_type,buff+9);

		else if (strstr(buff,"APP_VERSION:") != NULL )
		{
			strcpy(A_ver,buff+12);
			break;
		}
		memset(buff,0x00,sizeof(buff));
	}


	return 0;
}


void get_uid(char *uid)
{

	FILE *fp;
	char buff[128];


	fp=fopen("/proc/cpuinfo","r");

	if(fp==NULL)
	{

		fprintf(stderr,"cpuinfo file open error\n");
		strcpy(uid,"ERROR");
		return ;

	}

	while(fgets(buff,sizeof(buff),fp)!=NULL)
	{

		if(strstr(buff,"Serial") != NULL)
		{
			strcpy( uid,buff+ 10 );
			break;
		}	
		memset(buff,0,sizeof(buff));
	}

	if(uid[strlen(uid)-1] == '\n')
		uid[strlen(uid)-1] = '\0';

	fclose(fp);

	return;
}

void get_project_name(char *name)
{
	FILE *fp;
	char buff[128];


	fp=fopen("/etc/rtm_response","r");

	if(fp==NULL)
	{

		fprintf(stderr,"rtm_response file open error");
		strcpy(name,"ERROR");
		return ;

	}

	while(fgets(buff,sizeof(buff),fp)!=NULL)
	{
		if(strstr(buff,"ProjectName:")!= NULL)
		{
			strcpy(name,buff+12);
			break;
		}	
		memset(buff,0,sizeof(buff));
	}
	if(name[strlen(name)-1] == '\n')
		name[strlen(name)-1] = '\0';


	fclose(fp);

	return;
}




int get_Machineid(char *machineid)
{

	int ret=0;

	FILE *fp=NULL;

	ret = system("fw_printenv machineid | grep machineid= | cut -d '=' -f2 > /tmp/machineid");

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

	if ( strlen(machineid) == 0 )
		return -1;
	else 
		return 0;

}
int get_macid(char *macid)
{
	typedef unsigned char UC;
	struct ifreq ifr;
	int fd=0;
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name,"eth0", IFNAMSIZ-1);
	if(ioctl(fd,SIOCGIFHWADDR, &ifr) <0){
		close(fd);
		return -1;
	}
	close(fd);

	sprintf(macid,"%02X:%02X:%02X:%02X:%02X:%02X",(UC)ifr.ifr_hwaddr.sa_data[0],(UC)ifr.ifr_hwaddr.sa_data[1],
			(UC)ifr.ifr_hwaddr.sa_data[2], (UC)ifr.ifr_hwaddr.sa_data[3],
			(UC)ifr.ifr_hwaddr.sa_data[4], (UC)ifr.ifr_hwaddr.sa_data[5]);
	sprintf(MACID,"%02X%02X%02X%02X%02X%02X",(UC)ifr.ifr_hwaddr.sa_data[0], (UC)ifr.ifr_hwaddr.sa_data[1],
			(UC)ifr.ifr_hwaddr.sa_data[2], (UC)ifr.ifr_hwaddr.sa_data[3],
			(UC)ifr.ifr_hwaddr.sa_data[4], (UC)ifr.ifr_hwaddr.sa_data[5]);
	return 0;
}


int Get_String_file(char *Path, char *Line)
{
	FILE* fp=NULL;
	size_t size=0;
	char *str=NULL;

	fp=fopen(Path, "r");
	if(fp==NULL){
		fprintf(stderr,"LIB#%s File Open Error\n",Path);
		fclose(fp);
		return -1;
	}
	getline(&str, &size, fp);
	str[strlen(str)-1]='\0';
	strcpy(Line, str);
	fclose(fp);
	return 0;
}



int bootloader_details(char *Bver)
{
	system("fw_printenv ver | cut -c5-32 > /tmp/Bver");
	if(Get_String_file("/tmp/Bver", Bver) <0){
		remove("/tmp/Bver");
		return -1;
	}
	remove("/tmp/Bver");
	return 0;
}

int kernel_details(char *kernelver)
{
	int fd,i,j;
	char buff[1048700]="",data[64];

	fd=open("/dev/mmcblk0",O_RDONLY);
	if(fd < 0){
		fprintf(stderr,"File open error\n");
		return -1;
	}
	if ( 1048576+64 != read(fd,buff,1048576+64))
		return -1;

	for (i=(1048576+32),j=0;i<1048576+62;i++,j++)
		data [j]=buff[i];

	data [j]='\0';
	strcpy(kernelver,data);
	close(fd);
	return 0;
}
int rootfs_details(char *rootfsver)
{
	system("cat /etc/rc.d/rc.local | grep GL11-RD | cut -c8-32 > /tmp/rootfsver");
	if(Get_String_file("/tmp/rootfsver", rootfsver) <0){
		return -1;
	}
	return 0;
}
int patch_ver(char *version)
{
	FILE *fp = NULL;

	char *line=NULL,*str=NULL;

	size_t len=20;
	char buff[20]="";
	fp = fopen("/etc/visiontek_release","r");
	if(fp == NULL)
	{
		fprintf(stdout,"Patch Details Unavailable\n");
		strcpy(version,"ERROR");
		return -1;
	}
	while((getline(&line, &len, fp)) > 0)
	{
		if((str = (char *)strstr(line,"PATCH_VERSION=")) != NULL)
		{

			strcpy(buff,str+14);
			if(buff[strlen(buff)-1] == '\n')
				buff[strlen(buff)-1]='\0';

			sprintf(version,"%s",buff);
			break;
		}

	}
	if( strlen(version) == 0 )
		strcpy(version,"ERROR");
	free(line);
	line=NULL;
	fclose(fp);
	return 0;
}

