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
	{ 0x74c86cc0, "init_timer_key" },
	{ 0x1920b184, "__register_chrdev" },
	{ 0xfe990052, "gpio_free" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xe75db9cf, "call_usermodehelper_exec" },
	{ 0x9b267c71, "call_usermodehelper_setfns" },
	{ 0x9e27a957, "call_usermodehelper_setup" },
	{ 0x8cfc414e, "add_timer" },
	{ 0x7d11c268, "jiffies" },
	{ 0x8949858b, "schedule_work" },
	{ 0x6d04c571, "key_buzzer_onoff_flag" },
	{ 0xd0a9cc31, "backlight_timeout" },
	{ 0x10227b59, "touch_buzzer_onoff_flag" },
	{ 0x67c2fa54, "__copy_to_user" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
	{ 0x27e1a049, "printk" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

