
#define MINORBITS       20
#define MKDEV(ma,mi)    (((ma) << MINORBITS) | (mi))
#define MINORMASK       ((1U << MINORBITS) - 1)

#define MAJOR(dev)      ((unsigned int) ((dev) >> MINORBITS))
#define MINOR(dev)      ((unsigned int) ((dev) & MINORMASK))

#include<stdio.h>

void bin(unsigned n)
{
    /* step 1 */
    if (n > 1)
        bin(n / 2);
 
    /* step 2 */
    printf("%d", n % 2);
}
int main()
{
unsigned int k;

k= MKDEV(4000,1048570);
k= (1U << MINORBITS )-0;
bin(k);
//for(int i=32;i>0;i--)
//printf("%d ",(k<<i) & 1);
printf("Value = %d = MAJOR = %d MINOR(dev) = %d \n",k,MAJOR(k),MINOR(k));
return 0;
}
