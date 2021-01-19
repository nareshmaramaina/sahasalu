#include<stdio.h>
#include<error.h>
#include<dirent.h>
int main(int argc,char *argv[])
{
DIR *dp;
struct dirent *dirp;
dp=opendir(argv[1]);
dirp=readdir(dp);
while(dirp!=NULL)
printf("%s\n",dirp->d_name);

}
