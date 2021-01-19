
#include <sys/time.h>
       #include <sys/resource.h>
#include<stdio.h>
int main()
{
struct rlimit v;
getrlimit(RLIMIT_STACK,&v);
printf("%u...\n%u..\n",v.rlim_cur,v.rlim_max);

}
