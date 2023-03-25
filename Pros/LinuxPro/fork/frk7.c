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
	fd = open("./test", O_RDONLY);
	cpid = fork();
//       fd = open("./test",O_RDONLY);
	if (cpid == CHILD) {
		read(fd, buf, 2);
		printf(" child:  %c\n", buf[0]);
		printf(" child: %c\n", buf[1]);
		close(fd);
	}
	// parent
	else {
		wait(&childstatus);
		read(fd, buf, 2);
		printf(" parent: %c\n", buf[0]);
		printf(" parent: %c\n", buf[1]);
		close(fd);
	}
	return 0;
}
