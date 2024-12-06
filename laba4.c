#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/random.h>

static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) {
    static char buffer[512];
    static int len = 0;
    static int finished = 0;

    if (finished) {
        finished = 0;
        return 0;
    }

    int start = 5; // начальный элемент прогрессии
    int step = 3;  // шаг прогрессии
    int num_elements;

    get_random_bytes(&num_elements, sizeof(num_elements));
    num_elements = (abs(num_elements) % 11) + 5;

    len = snprintf(buffer, sizeof(buffer), "Количество членов арифметической прогрессии: %d\nСуммы:\n", num_elements);

    int sum = 0;
    for (int i = 0; i < num_elements; i++) {
        sum += start + i * step;
        len += snprintf(buffer + len, sizeof(buffer) - len, "%d\n", sum);
    }

    if (copy_to_user(buf, buffer, len)) {
        return -EFAULT;
    }

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
