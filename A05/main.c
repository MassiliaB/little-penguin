#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>

#define DEVICE_NAME "fortytwo"
#define LOGIN "root"

static ssize_t read_misc(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    return simple_read_from_buffer(buf, len, offset, LOGIN, sizeof((LOGIN) - 1));
}

static ssize_t write_misc(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    ssize_t ret;
    char user_buf[69];

    ret = simple_write_to_buffer(user_buf, 69, offset, buf, len);
    if (ret > 0) {
        pr_info("Received data: %s\n", user_buf); 
        if (strcmp(user_buf, LOGIN) == 0)
	    return ret;
    }
    return -EINVAL;
}

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = read_misc,
    .write = write_misc,
};

static struct miscdevice misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &fops,
};

static int __init init_module_misc(void) {
    printk(KERN_INFO "Loading misc_device module\n"); 
    return misc_register(&misc_device);
}

static void __exit exit_module_misc(void) {
    printk(KERN_INFO "Exiting misc_device module\n"); 
    misc_deregister(&misc_device);
}

module_init(init_module_misc);
module_exit(exit_module_misc);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module for creating misc device");
