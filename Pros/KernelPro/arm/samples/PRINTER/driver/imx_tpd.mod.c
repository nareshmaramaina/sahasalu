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
	{ 0x1920b184, "__register_chrdev" },
	{ 0xfe990052, "gpio_free" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x2db6ffff, "mxc_iomux_v3_setup_pad" },
	{ 0x43b0c9c3, "preempt_schedule" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xfbc74f64, "__copy_from_user" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

