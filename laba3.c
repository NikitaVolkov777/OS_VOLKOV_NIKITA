#include <linux/kernel.h>
#include <linux/module.h> 
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Volkov Nikita group 932220");
MODULE_DESCRIPTION("Simple kernel model");
MODULE_VERSION("0.1");

static int __init Module_init(void) {
    pr_info("Welcome to the Tomsk State University\n");
    return 0;
}

static void __exit Module_exit(void) {
    pr_info("Tomsk State University forever!\n");
}

module_init(Module_init);
module_exit(Module_exit);
