#include <sys/types.h>
       #include <utime.h>
#include<stdio.h>
#include<time.h>
void main()
{
struct utimbuf v;
v.actime=0;
v.modtime=0;
utime("alaram.c",&v);
}
