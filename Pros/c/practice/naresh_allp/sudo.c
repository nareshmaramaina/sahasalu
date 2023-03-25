#include<stdio.h>
int main()
{
	FILE *fp=NULL;
	char buff[]="123456";
	fp=popen("su","w");
	fwrite(buff,1,8,fp);
	pclose(fp);
}
