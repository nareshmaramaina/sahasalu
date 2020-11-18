/* test application to show how to load shared objects as runtime libs */
#include <stdio.h>
#include <dlfcn.h>

int main()
{
	void *ptr;
	void (*fptr) (void);
	
	printf("in main\n");
	getchar();

	/* load specified library */	
	ptr = dlopen("./one.so", RTLD_NOW);
	/* find address of  a symbol */
	fptr = dlsym(ptr, "test");
	
	(fptr)();/* indirect call */
	getchar();

	/* detach lib from process address space */
	dlclose(ptr);
	getchar();
	return 0;
}
