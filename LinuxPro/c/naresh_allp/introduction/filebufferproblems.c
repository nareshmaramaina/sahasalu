#include<stdio.h>
#include<unistd.h>
int main()
{
	FILE *fp;
	int cnt=0;
	char str[20]="this is jithu\n";
	while(1)
	{
		fp=fopen("file.txt","w");
		if(fp==NULL)
		{
			printf("error in open file:");
			return 0;
		}
		while(1)
		{
			fprintf(fp,"kkkkkkkkkkkkkkkkkkkkkkkkkkkk");
			if(cnt==1000)
				break;
			cnt++;
		}
//		while(1);
		fclose(fp);
break;
		//sleep(5);
	}
}
