#include<linux/module.h>
#include<linux/fs.h>
#include <linux/uaccess.h>

extern	int key_flag;
MODULE_LICENSE("GPL");
int symbol_init(void)
{
	pr_info("Inko init %d \n",key_flag);
	return 0;
}

void symbol_exit(void)
{

	pr_info("Exiting\n");
	return;
}

module_init(symbol_init);
module_exit(symbol_exit);
