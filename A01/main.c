#include <linux/module.h>
#include <linux/kernel.h>

static int __init init_hello_module(void) {
    printk(KERN_INFO "Hello world!\n");
    return 0;
}

static void __exit cleanup_hello_module(void) {
    printk(KERN_INFO "Cleaning up module.\n");
}

module_init(init_hello_module);
module_exit(cleanup_hello_module);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A simple Hello World kernel module");
