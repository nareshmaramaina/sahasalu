#include<stdio.h>
#include<unistd.h>
main()
{
if(fork()==0)
{
printf("childn process:");
exit(0);
}
else
printf("parent process:");
printf("other process\n");
}
