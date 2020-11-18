#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x59caa4c3, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x5e75e852, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xd21ce1eb, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x8c29ae20, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x8e7202cc, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0xb900cbdb, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0xd114464c, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0xc05b1b8e, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xace1a41b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xf9c0b663, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0x5792f848, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xd58543db, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0xc930d5a7, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x5d570e8e, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0x68565378, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xdab9e674, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf812cff6, __VMLINUX_SYMBOL_STR(memscan) },
	{ 0x6232b4e3, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x2dc603f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x9b3f67da, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xdc0accc3, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic03isc01ip01in*");

MODULE_INFO(srcversion, "928898F3BE16D53381D4613");
