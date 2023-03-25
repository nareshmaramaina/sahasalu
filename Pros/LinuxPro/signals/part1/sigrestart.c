#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define DEATH(mess) { perror(mess); exit(errno); }

void handler(int signum)
{
	printf("\n %s: \n",__func__);
	printf("We have received signal :  %d \n", signum);
	printf(" exit from sighandler \n");
}

int main(int argc, char *argv[])
{
	struct sigaction act;
	int fd, ret;
	char buf[30];

	memset(&act, 0, sizeof(act));

	act.sa_flags = SA_RESTART;
	act.sa_handler = handler;
	if (sigaction(SIGINT, &act, NULL) < 0)	/* for CTRL-C */
		DEATH("sigaction");

	printf("Successfully installed signal handler for SIGINT\n");

	fd = open("./myfifo", O_RDWR);
	if (fd < 0)
		DEATH("OPEN:");

	ret = read(fd, buf, 30);
	if (ret < 0)
		perror("read:");

	printf("no of bytes read %d : data read %s \n", ret, buf);

	exit(EXIT_SUCCESS);
}
