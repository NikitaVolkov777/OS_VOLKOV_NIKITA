#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

static int K = 1;

static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) {
    static char buffer[128];
    static int finished = 0;

    if (finished) {
        finished = 0;
        return 0;
    }

    int start = 5; // начальный элемент прогрессии
    int step = 3;  // шаг прогрессии

    int sum = K * (2 * start + (K - 1) * step) / 2;

    int len = snprintf(buffer, sizeof(buffer), "Количество членов арифметической прогрессии: %d\nСумма членов арифметической прогрессии: %d\n", K, sum);

    if (copy_to_user(buf, buffer, len)) {
        return -EFAULT;
    }

    K++;
    finished = 1;
    return len;
}

static struct proc_dir_entry *proc_file;
static const struct proc_ops proc_file_ops = {
    .proc_read = proc_read,
};

static int __init my_init(void) {
    proc_file = proc_create("tsulab", 0444, NULL, &proc_file_ops);
    if (!proc_file) {
        pr_err("Не удалось создать файл в /proc\n");
        return -ENOMEM;
    }

    pr_info("Модуль загружен: файл %s создан в /proc\n", "tsulab");
    return 0;
}

static void __exit my_exit(void) {
    if (proc_file) {
        proc_remove(proc_file);
        pr_info("Файл %s удален из /proc\n", "tsulab");
    }

    pr_info("Tomsk State University forever!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
