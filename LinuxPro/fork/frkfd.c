#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

#define CHILD 0

int main()
{
	int fd;
	char buf[2];
	pid_t cpid;
	int childstatus;
//	fd = open("./test", O_RDONLY);
	cpid = fork();
        fd = open("./test",O_RDONLY);
	if (cpid == CHILD) {
		close(1);
		read(fd, buf, 2);
		printf("CHILD:\n");
		printf(" in child %c\n", buf[0]);
		printf(" in child %c\n", buf[1]);
		close(fd);// COW
	}
	// parent
	else {
		wait(&childstatus);
		read(fd, buf, 2);
		printf("PARENT\n");
		printf(" in parent %c\n", buf[0]);
		printf(" in parent %c\n", buf[1]);
		close(fd);
	}
	exit(EXIT_SUCCESS);
}
