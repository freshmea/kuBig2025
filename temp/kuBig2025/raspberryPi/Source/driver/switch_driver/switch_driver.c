#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

#define DEV_MAJOR_NUMBER	222
#define DEV_NAME		"switch_driver"

int sw[4] = {4,17,27,22};

static ssize_t switch_driver_read(struct file * file, char * buf, size_t length, loff_t * ofs){
	int ret,i;
	char read_buf[4];
	printk(KERN_INFO "switch_driver_read!\n");
	for(i=0;i<4;i++)
		read_buf[i] = gpio_get_value(sw[i]);
	ret = copy_to_user(buf,read_buf,sizeof(read_buf));
	if(ret<0)
		printk(KERN_INFO "switch driver copy to user failed!\n");
	return 0;
}

static int switch_driver_open(struct inode * inode, struct file * file){
	int ret,i;
	printk(KERN_INFO "switch_driver_open!\n");
	for(i=0;i<4;i++){
		ret = gpio_request(sw[i],"sw");
		if(ret<0)
			printk(KERN_INFO "switch driver gpio_request failed!\n");
	}
	return 0;
}

static int switch_driver_release(struct inode * inode, struct file * file){
	int i;
	printk(KERN_INFO "switch_driver_release!\n");
	for(i=0;i<4;i++)
		gpio_free(sw[i]);
	return 0;
}

static struct file_operations switch_driver_fops = {
	.owner = THIS_MODULE,
	.open = switch_driver_open,
	.release = switch_driver_release,
	.read = switch_driver_read,
};

static int switch_driver_init(void){
	printk(KERN_INFO "switch_driver_init!\n");
	register_chrdev(DEV_MAJOR_NUMBER,DEV_NAME,&switch_driver_fops);
	return 0;
}

static void switch_driver_exit(void){
	printk(KERN_INFO "switch_driver_exit!\n");
	unregister_chrdev(DEV_MAJOR_NUMBER,DEV_NAME);
}

module_init(switch_driver_init);
module_exit(switch_driver_exit);
MODULE_LICENSE("GPL");
