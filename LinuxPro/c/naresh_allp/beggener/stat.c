#include<stdlib.h>
#include<stdio.h>
#include<error.h>
       #include <unistd.h>
   #include <sys/types.h>
       #include <sys/stat.h>
int main(int argc,char *argv[])
{
	int i;
	struct stat buf;
	printf("information of lstat function\n");
	for(i=1;i<argc;i++)
		if(stat(argv[i],&buf)!=0)
			perror("error:");
		else
		{
			printf("inode for %s-----%ld\n",argv[i],buf.st_ino);
			printf("	hardlinks%ld\n",buf.st_nlink);
			printf("	softlinksize%ld\n",buf.st_size);
			printf("	block size%ld\n",buf.st_blksize);
			printf("	no of blocks%ld\n",buf.st_blocks);
		}
	printf("information of stat function\n");
	for(i=1;i<argc;i++)
		if(stat(argv[i],&buf)!=0)
			perror("error:");
		else
		{
			printf("inode for %s-----%ld\n",argv[i],buf.st_ino);
			printf("        hardlinks%ld\n",buf.st_nlink);
			printf("        softlinksize%ld\n",buf.st_size);
			printf("        block size%ld\n",buf.st_blksize);
			printf("        no of blocks%ld\n",buf.st_blocks);
		}

}
