#include<string.h> 
#include <sys/ipc.h>
       #include <sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
key_t key=1235;
int shmid;
char *sharemem;
shmid=shmget(key,40,0666|IPC_CREAT);
sharemem=shmat(shmid,NULL,0);
scanf("%s",sharemem);
puts(sharemem);
}
