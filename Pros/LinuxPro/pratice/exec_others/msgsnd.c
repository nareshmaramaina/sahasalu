#include<string.h>
#include<stdio.h>
#include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>
int main()
{
int msgid;
char str[100];
key_t key;
if(key=ftok("scanf.c",'B')==-1)
perror("ftok\n");
printf("%d\n",key);
msgid=msgget(key,0666|IPC_CREAT);
printf("enter the message for send\n");
scanf("%s",str);
if(msgsnd(msgid,str, strlen(str)+1,0)==-1)
perror("error:");
}

