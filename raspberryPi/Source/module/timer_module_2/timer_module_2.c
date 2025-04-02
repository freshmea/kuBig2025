#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>

static struct timer_list timer;

static void timer_cb(struct timer_list *timer){
	printk(KERN_INFO "timer callback function ! \n");
	timer->expires = jiffies + HZ * 4;
	add_timer(timer);
}

static int timer_module_init_2(void){
	printk(KERN_INFO "timer_module_init_2!\n");
	timer_setup(&timer,timer_cb,0);
	timer.expires = jiffies + HZ * 4;
	add_timer(&timer);
	return 0;
}

static void timer_module_exit_2(void){
	printk(KERN_INFO "timer_module_exit_2!\n");
	del_timer(&timer);
}

module_init(timer_module_init_2);
module_exit(timer_module_exit_2);
MODULE_LICENSE("GPL");
