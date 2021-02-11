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
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xd8f795ca, "del_timer" },
	{ 0xf9a482f9, "msleep" },
	{ 0x8cfc414e, "add_timer" },
	{ 0x74c86cc0, "init_timer_key" },
	{ 0x27deb9e2, "wake_up_process" },
	{ 0x7c11f31e, "kthread_create_on_node" },
	{ 0x1920b184, "__register_chrdev" },
	{ 0xfe990052, "gpio_free" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x4b456689, "touch_pnt_out" },
	{ 0x7cb5a323, "key_out_flag" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0x8893fa5d, "finish_wait" },
	{ 0x75a17bed, "prepare_to_wait" },
	{ 0x1000e51, "schedule" },
	{ 0xdc43a9c8, "daemonize" },
	{ 0x9a6221c5, "mod_timer" },
	{ 0xb9e52429, "__wake_up" },
	{ 0x7d11c268, "jiffies" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x27e1a049, "printk" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=matrix_keypad";

