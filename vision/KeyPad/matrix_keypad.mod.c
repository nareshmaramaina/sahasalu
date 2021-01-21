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
	{ 0xd66b7075, "kmalloc_caches" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xd8f795ca, "del_timer" },
	{ 0xccdc1ea2, "dev_set_drvdata" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x432fd7f6, "__gpio_set_value" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x74c86cc0, "init_timer_key" },
	{ 0x7d11c268, "jiffies" },
	{ 0xce2840e7, "irq_set_irq_wake" },
	{ 0xcdffe94b, "input_event" },
	{ 0xfa2a45e, "__memzero" },
	{ 0x65d6d0f0, "gpio_direction_input" },
	{ 0xae00d767, "dev_err" },
	{ 0x2db6ffff, "mxc_iomux_v3_setup_pad" },
	{ 0x27e1a049, "printk" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0x1b780516, "input_set_capability" },
	{ 0x9a6221c5, "mod_timer" },
	{ 0x45e98630, "platform_driver_register" },
	{ 0x4f920224, "device_init_wakeup" },
	{ 0x1d26df1c, "kmem_cache_alloc" },
	{ 0x371bdb4f, "input_register_device" },
	{ 0xd0ebf0a8, "input_free_device" },
	{ 0xfe990052, "gpio_free" },
	{ 0x37a0cba, "kfree" },
	{ 0xff301e1a, "input_unregister_device" },
	{ 0x6c8d5ae8, "__gpio_get_value" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x30f78a53, "platform_driver_unregister" },
	{ 0xa170bbdb, "outer_cache" },
	{ 0xad6d7d07, "dev_get_drvdata" },
	{ 0xd378a879, "input_allocate_device" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

