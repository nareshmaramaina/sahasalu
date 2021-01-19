#include <unistd.h>
#include <stdlib.h>
int main()
{
char buf[23];
gets(buf);
if ((write(1, buf, 23)) != 18)
write(2, "A write error has occurred on file descriptor 1\n",46);
exit(0);
}
