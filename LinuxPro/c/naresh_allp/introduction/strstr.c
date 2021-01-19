#include<error.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char **argv)
{
int i;
FILE *fp;
fp=fopen("suresh.txt","a");
puts(argv[1]);
strcat(argv[1],argv[2]);
puts(argv[1]);
system(argv[1]);
//execlp("/","base64",argv[0],argv[1],NULL);
}
