#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{

printf(" ");

return 0;
}
           char *
           strncpy(char *dest, const char *src, size_t n)
           {
               size_t i;

               for (i = 0; i < n && src[i] != '\0'; i++)
                   dest[i] = src[i];
               for ( ; i < n; i++)
                   dest[i] = '\0';

               return dest;
           }

