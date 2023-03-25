#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
	int
main ( int argc, char *argv[] )
{
	if ( argc < 2 )
	return -1;

	int fd = 	open(argv[1],O_TRUNC|O_WRONLY);

	
	if ( fd < 0 )
	return -1;
	write(fd,"Naresh",6);	
	close(fd);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
