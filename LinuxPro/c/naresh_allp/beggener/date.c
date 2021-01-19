#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
void print_date  (void)
{
   time_t rawtime;
   struct tm *info;
   char buffer[80];

   time( &rawtime ); 
   info = localtime( &rawtime );
   sprintf(buffer ," -- %s", asctime(info));
printf(buffer);
}
int main()
{
print_date();
}
