#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
 #include <sys/time.h>
       #include <sys/resource.h>

int main()
{
struct rlimit rlim;
struct rlimit glim;
//glim.rlim_cur=1600000000;
//glim.rlim_max=1600000000;
     //  setrlimit(RLIMIT_STACK,&glim);
 getrlimit(RLIMIT_STACK,&rlim);
printf("softlimit=%lu,hardlimit=%lu\n",rlim.rlim_cur,rlim.rlim_max);
}
