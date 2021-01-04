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

void Func(unsigned long data);
DECLARE_TASKLET(Tasklet,Func,1);
//tasklet_struct 
void Func(unsigned long data)
{
	//	pr_info("data = %d\n",data);
	int ret;
	pr_info("Entering TASKLET t_fun, ,in context of %s with pid = %d\n",               current->comm, current->pid);
	ret = in_interrupt();
	if ( ret )
		pr_info(" in Interrupt Context %d\n",ret);
	else 
		pr_info(" in Process Context %d\n",ret);


	return;
}
irq_handler_t irq_handler( int irq_no)
{
	int ret;
	pr_info("IRQ raised is %d\n",irq_no);
	ret = in_interrupt();
	if ( ret )
		pr_info(" in Interrupt Context %d\n",ret);
	else 
		pr_info(" in Process Context %d\n",ret);

	pr_info("Entering IRQ, ,in context of %s with pid = %d\n",current->comm, current->pid);

	tasklet_schedule(&Tasklet);

	pr_info("Completion\n");
	return IRQ_HANDLED;
}


static int __init irq_ex_init(void)
{
	int ret;
	pr_info("Entering Init, ,in context of %s with pid = %d\n",               current->comm, current->pid);
	ret = in_interrupt();
	if ( ret )
		pr_info(" in Interrupt Context %d\n",ret);
	else 
		pr_info(" in Process Context %d\n",ret);

	tasklet_schedule(&Tasklet);

	pr_info("Completion\n");	
	//	return request_irq (396, (irq_handler_t) irq_handler,IRQF_SHARED, "irq_handler",(void *)(irq_handler));
}

static void __exit irq_ex_exit(void)
{
	pr_info("Chill\n");
	//	free_irq(396,);
}

module_init(irq_ex_init);
module_exit(irq_ex_exit);
