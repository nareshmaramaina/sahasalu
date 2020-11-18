#include<linux/module.h>

int mod_init(void)
{

	printk("Hello world");

	return 0;
}

void mod_exit(void)
{

	printk("in %s file ",__func__);
}
module_init(mod_init);
module_exit(mod_exit);
