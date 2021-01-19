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

if(msgrcv(msgid,(void*)&buff,512,0,0)!=-1)
printf("you wrote:%s\n",buff);
else perror("error:");
if(strncmp(buff,"end",3)==0)
flag=0;
}
exit(0);
}
