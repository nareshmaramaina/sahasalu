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
	{ 0x3eeb1285, "kthread_stop" },
	{ 0x27deb9e2, "wake_up_process" },
	{ 0x7c11f31e, "kthread_create_on_node" },
	{ 0xf6288e02, "__init_waitqueue_head" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x8893fa5d, "finish_wait" },
	{ 0x75a17bed, "prepare_to_wait" },
	{ 0x1000e51, "schedule" },
	{ 0x5f754e5a, "memset" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x27e1a049, "printk" },
	{ 0xd2965f6f, "kthread_should_stop" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

