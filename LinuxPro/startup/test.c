/* entry point test */
# include <stdio.h>
# include <stdlib.h>

/* program entry point */
int _start()
{
	printf("\n %s: \n",__func__);
	printf("in start routine\n");
	xyz();
	_fini();
	exit(0);
}
/* start of functionality */
int xyz()
{
	printf("\n %s: \n",__func__);
	printf("begin of app functionality\n");
	return 0;
}
/* program destructor */
int _fini()
{
	printf("\n %s: \n",__func__);
	printf("cleanup invoked\n");
	return 0;
}	
