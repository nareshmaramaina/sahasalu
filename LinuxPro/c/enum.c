#include<stdio.h>
enum irqreturn {
        IRQ_NONE                = (0 << 0),
        IRQ_HANDLED             = (1 << 0),
        IRQ_WAKE_THREAD         = (1 << 1),
};

typedef enum irqreturn irqreturn_t;

int main()
{

printf(" %d IRQ_HANDLED = %d  IRQ_WAKE_THREAD =%d\n",sizeof(IRQ_HANDLED),IRQ_HANDLED,IRQ_WAKE_THREAD);

return 0;
}
