#include "stdio.h" 
int main()
{
	void *pVoid;
	pVoid = (void*)0;
	printf("%lu %d",sizeof(pVoid),sizeof(int));
	return 0;
}
