#include"headers.h"
int main()
{
int shmid;
void *buff;
key_t key=1;
size_t size=10;
if((shmid=shmget(key,size,0666|IPC_CREAT))!=-1)
printf("success\n");
else perror("dure to :");
if((buff=shmat(shmid,NULL,0))!=EOF)
printf("success\n");
else perror("error:\n");
gets(buff);
puts(buff);

}
