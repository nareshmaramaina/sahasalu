#include<string.h>
#include<stdlib.h>
#include<stdio.h>
int main(int argc,char *argv[])
{
char ip[40]="";
if(argc<2)
{
puts("PLZ enter ip last\n");
return 0;
}
sprintf(ip,"ifconfig ens32 192.168.%s up",argv[1]);
system(ip);
memset(ip,0,40);
sprintf(ip,"route add default gw 192.168.%c.6",argv[1][0]);
system(ip);
return 0;
}
