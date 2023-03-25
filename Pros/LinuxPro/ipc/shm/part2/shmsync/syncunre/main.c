#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include "mydata.h"

int main()
{
	int fd;
	unsigned int value = 1;
	struct mydata *addr;
	pthread_mutexattr_t psharedm;

	pthread_mutexattr_init(&psharedm);
	pthread_mutexattr_setpshared(&psharedm,
                      PTHREAD_PROCESS_SHARED);

	fd = shm_open(DATA, O_CREAT | O_RDWR, 666);
	if (fd == -1) {
		perror("shm_open");
		exit(1);
	}

	/* 4k is min shared memory */
	if (ftruncate(fd, getpagesize()) == -1) {
		perror("ftruncate");
		exit(1);
	}

	addr =
	    (struct mydata *)mmap(NULL, sizeof(struct mydata),
				  PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	
	/* initialise */
	pthread_mutex_init(addr->mtxlock, &psharedm);
	addr->a = 0;
	addr->b = 0;

	munmap(addr, sizeof(struct mydata));

	return 0;
}
