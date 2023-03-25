#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
int main()
{
char block[1024];
int in, out;
int nread;
in = open("fork.c", O_RDONLY);
out = open("filling.txt", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
while((nread = read(in,block,sizeof(block))) > 0)
write(out,block,nread);
//printf("%s",block);
exit(0);
}
