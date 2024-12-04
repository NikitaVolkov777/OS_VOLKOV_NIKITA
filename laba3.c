#include <linux/kernel.h>
#include <linux/module.h> 
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/version.h>

static int __init Module_init(void) {
    pr_info("Welcome to the Tomsk State University\n");
    return 0;
}

static void __exit Module_exit(void) {
    pr_info("Tomsk State University forever!\n");
}

module_init(Module_init);
module_exit(Module_exit);
MODULE_LICENSE("GPL");
