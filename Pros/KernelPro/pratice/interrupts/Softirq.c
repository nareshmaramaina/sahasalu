/*
 * An interrupt handler
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <asm/io.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Naresh.m");
void soft_irq_handler(struct softirq_action *k)
{

	pr_info("Excecuting Soft irq Handler \n");

	return ;
}


irq_handler_t irq_handler( int irq_no)
{

	pr_info("IRQ raised is %d\n",irq_no);

	open_softirq(HI_SOFTIRQ,soft_irq_handler);	
	pr_info("While a handler runs, softirqs on the current processor are disabled, However another processs the ssame softirq can run\n");
	raise_softirq(HI_SOFTIRQ);	
	pr_info("Raised softirq \n");	
	return IRQ_HANDLED;
}


static int __init irq_ex_init(void)
{
	return request_irq (396, (irq_handler_t) irq_handler,IRQF_SHARED, "irq_handler",(void *)(irq_handler));
}

static void __exit irq_ex_exit(void)
{
	free_irq(396,NULL);
}

module_init(irq_ex_init);
module_exit(irq_ex_exit);
