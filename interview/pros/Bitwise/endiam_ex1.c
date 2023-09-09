#include<stdio.h>
int show(char *start, int size) {

	for ( int i=0;i < size;i++) {

		printf("%.2x",start[i]);
	}
	printf("\n");
	return 0;
}

int main() {

	int i=0x01234567;
	show((char*)&i,sizeof(int));

	return 0;
}
