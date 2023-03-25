#include<stdio.h>
int main()
{
char str[60]="nareshvisiontek",ptr[60];
//sprintf(ptr,"%s",str);
sscanf(str+6,"%s",ptr);
printf("%s\n",ptr);
//printf(str);
}
