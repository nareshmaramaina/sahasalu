#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xdb8f28a, "module_layout" },
	{ 0x3ec8886f, "param_ops_int" },
	{ 0x999e8297, "vfree" },
	{ 0x7b06feab, "blk_cleanup_queue" },
	{ 0xb5a459dc, "unregister_blkdev" },
	{ 0x10a10fe4, "put_disk" },
	{ 0xd5df264f, "del_gendisk" },
	{ 0x24c77e05, "add_disk" },
	{ 0x9d669763, "memcpy" },
	{ 0xda28b224, "alloc_disk" },
	{ 0x71a50dbc, "register_blkdev" },
	{ 0xed7dd85a, "blk_queue_logical_block_size" },
	{ 0xe56cb930, "blk_init_queue" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x27e1a049, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

