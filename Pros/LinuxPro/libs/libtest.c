#include <stdio.h>
#include "lib.h"
int main()
{
	printf("invoking 3rd party lib call\n");
	test(); // our lib call 
	printf("end of main\n");
	getchar();
	return 0;
}
