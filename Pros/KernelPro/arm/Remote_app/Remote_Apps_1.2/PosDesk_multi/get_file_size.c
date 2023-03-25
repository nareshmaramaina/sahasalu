#include<header.h>

int size_of_file(const char *file)
{
	struct stat buf;

	if(stat(file,&buf) != 0)
	{
		perror("error:");
		return 0;
	}

	else
		return buf.st_size;

}

