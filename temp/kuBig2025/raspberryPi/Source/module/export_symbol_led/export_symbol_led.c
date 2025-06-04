#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>

#define HIGH	1
#define LOW	0

int led[4] = {23,24,25,1};

void export_symbol_led_write(int *a){
	int ret,i;
	for(i=0;i<4;i++){
		ret = gpio_direction_output(led[i],a[i]);
	}
}
EXPORT_SYMBOL(export_symbol_led_write);

static int export_symbol_led_init(void){
	int ret,i;
	printk(KERN_INFO "export_symbol_led_init!\n");
	for(i=0;i<4;i++){
		ret = gpio_request(led[i],"LED");
		if(ret<0)
			printk(KERN_INFO "gpio_request failed!\n");
	}
	return 0;
}

static void export_symbol_led_exit(void){
	int i;
	printk(KERN_INFO "export_symbol_led_exit!\n");
	for(i=0;i<4;i++)
		gpio_free(led[i]);
}

module_init(export_symbol_led_init);
module_exit(export_symbol_led_exit);
MODULE_LICENSE("GPL");
