
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
int cwd_root;
int root_count;
int dir_count;
int main(int argc,char *argv[])
{
	int i=0,count=0,j=0;
	char command[100];
	char cwd[1024];
	int ret=0;
	char directories[78][20]={"/","root","/root/","/root","root/","bin","/bin","/bin/","bin/","sbin","/sbin","/sbin/","sbin/","lib","/lib","/lib/","lib/","usr","/usr","/usr/","usr/","home","/home","home/","/home/","etc","/etc","/etc/","etc/","var","/var","/var/","var/","mnt/sysuser","/mntsysuser/","mnt/sysuser/","opt","/opt","/opt/","opt/","share","/share","/share/","share/","sys","vision","vision/","/vision","/vision/","dev","/dev","/dev/","dev/","usr/bin","/usr/bin","/usr/bin/","usr/bin/","usr/etc","/usr/etc","/usr/etc","/usr/etc/","usr/include","/usr/include","usr/include/","/usr/include/","usr/lib","/usr/lib","usr/lib/","/usr/lib/","usr/sbin","/usr/sbin","usr/sbin/","/usr/sbin/","usr/share","/usr/share","usr/share/","/usr/share/"};
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		//		fprintf(stdout, "Current working dir: %s\n", cwd);
		if(strcmp(cwd,"/")==0)
			cwd_root=1;
	}
	for(i=0;i<argc;i++)
	{
		if(cwd_root==1)
		{
			j=0;
			while(j<76)
			{
				if(strcmp(argv[i],directories[j])==0)
				{
					root_count++;
				}
				j++;
			}
		}
	}
	//	printf("Total root_Count=%d\n",root_count);
	for(i=0;i<argc;i++)
	{
		j=0;
		while(j<76)
		{
			if(strcmp(argv[i],directories[j])==0)
			{
				dir_count++;
			}
			j++;
		}
	}
	//	printf("Total dir_Count=%d\n",dir_count);

	if(cwd_root ==1 && root_count > 5)
	{
		fprintf(stdout,"Permission Denied\n");
	}
	else if(dir_count > 0 )
	{
		fprintf(stdout,"Permission Denied\n");
	}
	else
	{
		for(i=1;i<argc;i++)	
		{
			memset(command,0x00,100);
			sprintf(command,"rm_old -rf %s",argv[i]);
			ret=system(command);
		}
	}
}





