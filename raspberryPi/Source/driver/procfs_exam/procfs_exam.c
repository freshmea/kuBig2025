#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define MODULE_NAME "procfs_example"

static struct proc_dir_entry *example_dir, *foo_file;

static int procfs_simple_show(struct seq_file *s, void *unused){
	seq_printf(s,"procfs test!\n");
	return 0;
}

static int procfs_exam_open(struct inode *inode, struct file *file){
	return single_open(file,procfs_simple_show,NULL);		
}

static const struct file_operations foo_ops = {
	.owner = THIS_MODULE,
	.open = procfs_exam_open,
	.read = seq_read,
	.release = seq_release
};

static int procfs_exam_init(void){
        int ret = 0;
		
        example_dir = proc_mkdir(MODULE_NAME, NULL);
        if(example_dir == NULL) {
                ret = -ENOMEM;
                goto out;
        }
        
		foo_file = proc_create("procfs_test_file",0,example_dir,&foo_ops);

        printk(KERN_INFO "procfs_exam_init\n");
        return 0;
out:
        return ret;
}

static void procfs_exam_exit(void){
        remove_proc_entry("procfs_test_file", example_dir);
        remove_proc_entry(MODULE_NAME, NULL);
        printk(KERN_INFO "procfs_exam_exit\n");
}

module_init(procfs_exam_init);
module_exit(procfs_exam_exit);
MODULE_LICENSE("GPL");