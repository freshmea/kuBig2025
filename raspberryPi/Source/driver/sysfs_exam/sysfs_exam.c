#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
 
char value[20];
 
static ssize_t show_value(struct device *dev, struct device_attribute *attr, char *buf) {
	printk(KERN_INFO "sysfs exam show value!\n");
    return snprintf(buf, PAGE_SIZE, "%s\n", value);
}
 
static ssize_t store_value(struct device *dev, struct device_attribute *attr, const char *buf, size_t count) {
    sscanf(buf, "%s", value);
	printk(KERN_INFO "sysfs exam store value!\n");
    return strnlen(buf, PAGE_SIZE);
}
 
static DEVICE_ATTR(value, S_IRUGO | S_IWUSR, show_value, store_value);
 
static void sysfs_exam_release(struct device *dev) {}
 
static struct platform_device pdev = {
    .name = "sysfs_exam",
    .id = -1,
    .dev = {
        .release = sysfs_exam_release,
    }
};
 
static int __init sysfs_exam_init(void) {
    int err = 0;
 
    memset(value, 0, sizeof(value));
    err = platform_device_register(&pdev);
    if (err) {
        printk(KERN_ERR "platform_device_register error\n");
        return err;
    }
 
    err = device_create_file(&pdev.dev, &dev_attr_value);
    if (err) {
        printk(KERN_ERR "sysfs file create error\n");
        goto sysfs_err;
    }
	
	printk(KERN_INFO "sysfs exam init!\n");
    return 0;
 
sysfs_err:
    platform_device_unregister(&pdev);
    return err;
}
 
static void __exit sysfs_exam_exit(void) {
    device_remove_file(&pdev.dev, &dev_attr_value);
    platform_device_unregister(&pdev);
	printk(KERN_INFO "sysfs exam exit!\n");
}
 
module_init(sysfs_exam_init);
module_exit(sysfs_exam_exit);
 
MODULE_LICENSE("GPL");
