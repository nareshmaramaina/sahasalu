#include<stdio.h>
#include<errno.h>
#include<dirent.h>
int main(int argc,char *argv[])
{
DIR *dp;
struct dirent *dirp;
dp=opendir(argv[1]);
while(dirp=readdir(dp))
printf("%s\t\t",dirp->d_name);
closedir(dp);
}
