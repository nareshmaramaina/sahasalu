/*P9.33 Program to dynamically allocate a 2-D array*/
#include<stdio.h>
#include<stdlib.h>
char main(void)
{
	char **a,i,j,rows,cols,n=4;
	char 	buff[128];
	for(i =0 ;i< n ; i++)
	{
	gets(buff);
	printf( " strlen = %d\n",strlen(buff));
	a[i]= (char *) malloc((i+1) * strlen(buff));
	puts(a[i]);
	}
	return 0;
}
