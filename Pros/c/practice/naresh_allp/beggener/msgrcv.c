#include<error.h>
#include<stdio.h>
#include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>
int main()
{
int msgid;
char str[100];
key_t key;
if(key=ftok("sharedmem.c",'B')==-1)
perror("ftok\n");
printf("%d\n",key);
if((msgid=msgget(key,0644))==-1)
perror("error");
if(msgrcv(msgid,str,100,0,0)==-1)
perror("error:");
printf("recevied msg is :%s",str);
}

