#include<linux/module.h>
#include<linux/fs.h>
#include <linux/uaccess.h>

extern	int key_flag=0;
MODULE_LICENSE("GPL");
int symbol_init(void)
{
	key_flag=50;
	EXPORT_SYMBOL(key_flag);
	pr_info("init %d \n",key_flag);
	return 0;
}

void symbol_exit(void)
{

	pr_info("Exiting\n");
	return;
}

module_init(symbol_init);
module_exit(symbol_exit);
