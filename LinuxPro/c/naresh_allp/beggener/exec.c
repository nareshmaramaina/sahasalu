#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char *arg[])
{
printf("printing......\n\n");
//system(arg[1]);
execlp("./pipe",arg[1],NULL);
printf("nothing\n");

}
