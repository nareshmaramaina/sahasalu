#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
 #include <sys/time.h>
       #include <sys/resource.h>

int main()
{
struct rlimit rlim;
struct rlimit glim;
glim.rlim_cur=0;
glim.rlim_max=0;
       setrlimit(RLIMIT_STACK,&glim);
getrlimit(RLIMIT_STACK,&rlim);
printf("softlimit=%lu,hardlimit=%lu\n",rlim.rlim_cur,rlim.rlim_max);
int a[20]={20,34,34,34,34};
printf("%d\n",a[4]);
while(1);
}
