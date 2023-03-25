#include <stdio.h>
#include <dlfcn.h>
int main()
{
	void (*fptr) (void);
	void *ptr;
	ptr = dlopen("./liba.so", RTLD_LAZY);
	
	fptr = dlsym(ptr, "common1");
	(fptr)();
	dlclose(ptr);
	ptr = dlopen("./libb.so", RTLD_LAZY);
	fptr = dlsym(ptr, "common2");

	(fptr)();
	dlclose(ptr);
	return 0;
}
