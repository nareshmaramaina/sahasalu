#include<stdio.h>
#include<string.h>
int main(int argc,char **argv,char **env)
{
for(int i=0;argv[i];i++)
printf("%s*****%s\n",argv[i],env[i]);
}
