#include<stdlib.h>
#include<unistd.h>
#include<error.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[],char *envp[])
{
//strcat(argv[2],argv[3]);
//printf("*****%s",argv[2]);
//system(argv[1]);
//system(argv[2]);
//system(argv[3]);
int ret;
//char *args[]={"ls","-la",NULL};
ret=execl(argv[2],argv[3],envp,NULL);
perror("error");
}
