#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>
#include <linux/nsproxy.h>
#include <linux/ns_common.h>
#include <linux/rbtree.h>
#include <../fs/mount.h>
#include <linux/mount.h>

#define MY_PROC_ENTRY "mymount"
#define PROC_FULL_PATH "/proc/mymount"

/* global variables for procfs folder and file */
static struct proc_dir_entry *proc_file;

static void get_full_path(struct seq_file *seq, struct path *path)
{
    char *buf;
    char *path_str;

    buf = kmalloc(PATH_MAX, GFP_KERNEL);
    if (!buf)
        return;

    path_str = d_path(path, buf, PATH_MAX);
    if (!IS_ERR(path_str))
        seq_printf(seq, "%s", path_str);  
    kfree(buf);
}


static int print_mounts(struct seq_file *seq, void *ptr)
{
    struct rb_root mounts;
    struct mount *mnt, *tmp;
    struct super_block *sb;
    struct path path;

    mounts = current->nsproxy->mnt_ns->mounts;
    rbtree_postorder_for_each_entry_safe(mnt, tmp, &mounts, mnt_node) {
        sb = mnt->mnt.mnt_sb;
        path.mnt = &mnt->mnt;
        path.dentry = mnt->mnt.mnt_root;
        seq_printf(seq, "%s ", sb->s_id);
        get_full_path(seq, &path);
        seq_puts(seq, "\n");
    }
    return 0;
}

static int open_proc(struct inode *inode, struct file *file)
{
    return single_open(file, print_mounts, NULL);
}

static struct proc_ops p_fops = {
    .proc_open = open_proc,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init init_proc_entry(void) {
    proc_file = proc_create(MY_PROC_ENTRY, 0666, NULL, &p_fops);
    if (proc_file == NULL) {
	return -ENOMEM;
    }
   pr_info("mymounts créé avec succès");
   return 0;
}

static void __exit exit_proc_entry(void) {
    remove_proc_entry(MY_PROC_ENTRY, NULL);
}


module_init(init_proc_entry);
module_exit(exit_proc_entry);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module for creating misc device");
