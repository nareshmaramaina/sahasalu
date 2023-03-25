#include<stdio.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
int i;
for(i=1;argv[i];i++)
{
printf("i**************completed\n");
execvp("./list",argv+i);
}
printf("completed\n");
execvp("./dirent",argv+1);
}
