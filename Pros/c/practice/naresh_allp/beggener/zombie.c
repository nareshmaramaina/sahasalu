#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main()
{
if(fork()==0)
{
printf("%d\n",getpid());
printf("iam child\n");
exit(0);
}
wait(NULL);
printf("%d\n",getpid());
while(1);
/*else 
{
printf("iam child\n");
exit();
}*/

}
