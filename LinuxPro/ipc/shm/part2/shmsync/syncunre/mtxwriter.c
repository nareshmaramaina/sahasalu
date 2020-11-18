#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <mtxmydata.h>

int main()
{
	int fd;
	unsigned int value = 1;
	struct mydata *addr;

	fd = shm_open(DATA, O_RDWR, 0);
	if (fd == -1) {
		perror("shm_open");
		exit(1);
	}

	addr =
	    (struct mydata *)mmap(NULL, sizeof(struct mydata),
				  PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	pthread_mutex_lock (&addr->mtxlock);
	addr->a = 10;
	sleep(10);
	addr->b = 30;
	pthread_mutex_lock (&addr->mtxlock);
	munmap(addr, sizeof(struct mydata));

	return 0;
}
