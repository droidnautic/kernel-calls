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
	{ 0xdb68a6ee, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xd10868da, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x7a41e09a, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xe9124465, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x2c6af58e, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x2d5d0bb5, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xbe85e47c, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xe8ef0ff0, __VMLINUX_SYMBOL_STR(current_kernel_time64) },
	{ 0x211f68f1, __VMLINUX_SYMBOL_STR(getnstimeofday64) },
	{ 0x16edd3d0, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x6c706298, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A9F21D880BC96ED395C9A23");
