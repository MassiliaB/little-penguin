#include <linux/init.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DIRECTORY "fortytwo" 
#define ID_FILE "id"
#define JIFFIES_FILE "jiffies"
#define FOO_FILE "foo"        
#define LOGIN "root\n"

static struct dentry *dir, *id_file, *jiffies_file, *foo_file;
static char *foo_data;
static DEFINE_MUTEX(foo_mutex);
static size_t size;

/* read and write for id file*/
static ssize_t id_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    return simple_read_from_buffer(buf, len, offset, "root\n", sizeof((LOGIN) - 1));
}

static ssize_t id_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
    ssize_t ret;
    char user_buf[69];

    ret = simple_write_to_buffer(user_buf, 69, offset, buf, len);
    if (ret > 0) {
        if (strcmp(user_buf, LOGIN) == 0)
	    return ret;
    }
    return -EINVAL;
}

/*Read for joffies */
static ssize_t jiffies_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
    unsigned char jiffies_buf[69];
    
    snprintf(jiffies_buf, 69, "%lu\n", jiffies);
    return simple_read_from_buffer(buf, len, offset, jiffies_buf, strlen(jiffies_buf));
}

/* read and write for foo file */
static ssize_t foo_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    ssize_t ret;
    
    mutex_lock(&foo_mutex); 
    ret = simple_read_from_buffer(buf, len, offset, foo_data, size);
    mutex_unlock(&foo_mutex);
    return ret;
}

static ssize_t foo_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) 
{
   ssize_t ret;
    mutex_lock(&foo_mutex); 
    ret = simple_write_to_buffer(foo_data, PAGE_SIZE, offset, buf, len);

    if (ret > 0)
	size = max_t(size_t, size, *offset);
    mutex_unlock(&foo_mutex);
    return len;
}

/* File operations structure for the files */
static const struct file_operations id_fops = {
    .owner = THIS_MODULE,
    .read = id_read,
    .write = id_write,
};

static const struct file_operations jiffies_fops = {
    .owner = THIS_MODULE,
    .read = jiffies_read,
};

static const struct file_operations foo_fops = {
    .owner = THIS_MODULE,
    .read = foo_read,
    .write = foo_write,
};

static int __init init_debugfs(void) 
{
    //create directory
    dir = debugfs_create_dir(DIRECTORY, NULL);
    if (!dir)
        return -ENOMEM;

    // create files
    id_file = debugfs_create_file(ID_FILE, 0666, dir, NULL, &id_fops);
    jiffies_file = debugfs_create_file(JIFFIES_FILE, 0444, dir, NULL, &jiffies_fops);

    if (!id_file || !jiffies_file) {
        debugfs_remove_recursive(dir);
        return -ENOMEM;
    }

    // foo_data memory alloc
    foo_data = kzalloc(PAGE_SIZE, GFP_KERNEL);
    if (!foo_data) {
        debugfs_remove_recursive(dir);
        return -ENOMEM;
    }
    foo_file = debugfs_create_file(FOO_FILE, 0644, dir, NULL, &foo_fops);
    if (!foo_file)
        return -ENOMEM;

    return 0;
}

static void __exit exit_debugfs(void) {
    kfree(foo_data); 
    debugfs_remove_recursive(dir); 
}

module_init(init_debugfs);
module_exit(exit_debugfs);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module for testing debugfs");
