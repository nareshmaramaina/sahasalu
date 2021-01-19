#include<stdlib.h>
#include<stdio.h>
 #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/msg.h>
int main()
{
char buff[512];
int flag=1,value,msgid;
msgid=msgget((key_t)123,0777 | IPC_CREAT);
if (msgid == -1) {
perror("eee:");
exit(EXIT_FAILURE);
}
while(flag)
{
printf("enter text:");
scanf("%s",buff);
if(strcmp(buff,"end")==0)
flag=0;

if(msgsnd(msgid,(void*)buff,512,0)!=-1)
printf("sending....\n");
else perror("error:");
}
exit(0);
}
