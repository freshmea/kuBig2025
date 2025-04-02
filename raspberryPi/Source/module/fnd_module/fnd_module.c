#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define LOW		0
#define HIGH	1

#define DATA_PIN	0
#define LATCH_PIN	5
#define CLOCK_PIN	6

static int fnd_module_init(void){
	int ret,i;
	printk(KERN_INFO "fnd_module_init!\n");
	ret = gpio_request(DATA_PIN,"fnd");
	if(ret<0)
		printk(KERN_INFO "fnd_module gpio_request failed!\n");
	gpio_direction_output(DATA_PIN,LOW);
	ret = gpio_request(LATCH_PIN,"fnd");
	if(ret<0)
		printk(KERN_INFO "fnd_module gpio_request failed!\n");
	gpio_direction_output(LATCH_PIN,LOW);
	ret = gpio_request(CLOCK_PIN,"fnd");
	if(ret<0)
		printk(KERN_INFO "fnd_module gpio_request failed!\n");
	gpio_direction_output(CLOCK_PIN,HIGH);
	
	for(i=0;i<16;i++){
		gpio_direction_output(LATCH_PIN,LOW);
		gpio_direction_output(CLOCK_PIN,LOW);
		gpio_direction_output(DATA_PIN,HIGH);
		gpio_direction_output(CLOCK_PIN,HIGH);
		gpio_direction_output(LATCH_PIN,HIGH);
	}
	return 0;
}

static void fnd_module_exit(void){
	int i;
	printk(KERN_INFO "fnd_module_exit!\n");
	gpio_direction_output(LATCH_PIN,LOW);
	for(i=0;i<16;i++){
		gpio_direction_output(LATCH_PIN,LOW);
		gpio_direction_output(CLOCK_PIN,LOW);
		gpio_direction_output(DATA_PIN,LOW);
		gpio_direction_output(CLOCK_PIN,HIGH);
		gpio_direction_output(LATCH_PIN,HIGH);
	}
	gpio_free(DATA_PIN);
	gpio_free(LATCH_PIN);
	gpio_free(CLOCK_PIN);
}

module_init(fnd_module_init);
module_exit(fnd_module_exit);
MODULE_LICENSE("GPL");
