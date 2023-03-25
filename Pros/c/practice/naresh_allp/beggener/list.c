#include<dirent.h>
#include<stdio.h>
#include<string.h>
int main()
{
	int i=0,len=0,line=97;
	DIR *dp;
	struct dirent *v;
	dp=opendir("./");
	while((v=readdir(dp)))
	{
		i=strlen(v->d_name);
		len=len+i;
		printf("%s",v->d_name);
		if(len<line)
{
			len=len+8;
putchar('\t');
}
		
		else
		{
			putchar('\n');
			i=0;len=0;
		}
	}
			putchar('\n');
}
