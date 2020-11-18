#include<stdio.h>
char* func();
int main()
{
int *hi;
char str[10]; 
char *p= func( str);

puts(" Hi");
puts(p);
hi=&p;
printf(" %d \n",hi[0]);
return 0;
}

char* func(char str[])
{
strcpy(str,"Hello!"); 
return(str);
}
