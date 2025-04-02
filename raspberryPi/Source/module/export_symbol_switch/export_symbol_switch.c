#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/timer.h>

int sw[4] = {4,17,27,22};

static struct timer_list timer;

extern void export_symbol_led_write(int *a);

static void timer_cb(struct timer_list *timer){
	int sw_val[4],i;
	for(i=0;i<4;i++)
		sw_val[i] = gpio_get_value(sw[i]);
	export_symbol_led_write(sw_val);
	timer->expires = jiffies + HZ * 1;
	add_timer(timer);
}

static int export_symbol_switch_init(void){
	int ret,i;
	printk(KERN_INFO "export_symbol_switch_init!\n");
	for(i=0;i<4;i++){
		ret = gpio_request(sw[i],"sw");
		if(ret<0)
			printk(KERN_INFO "gpio_request failed!\n");
		else
			ret = gpio_direction_input(sw[i]);
	}
	timer_setup(&timer,timer_cb,0);
	timer.expires = jiffies + HZ * 1;
	add_timer(&timer);
	return 0;
}

static void export_symbol_switch_exit(void){
	int i;
	printk(KERN_INFO "export_symbole_switch_exit!\n");
	del_timer(&timer);
	for(i=0;i<4;i++)
		gpio_free(sw[i]);
}

module_init(export_symbol_switch_init);
module_exit(export_symbol_switch_exit);
MODULE_LICENSE("GPL");
