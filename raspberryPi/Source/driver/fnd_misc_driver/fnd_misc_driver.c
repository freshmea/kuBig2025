#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>

#define LOW		0
#define HIGH	1

#define DATA_PIN	0
#define LATCH_PIN	5
#define CLOCK_PIN	6

unsigned int ibuf[8];

int Getsegmentcode_base(int x)
{
	unsigned int i;

	for (i=0;i<8;i++)
		ibuf[i] = 0;

	switch(x){
		case 0 :
			for(i=1;i<7;i++) 
				ibuf[i] = 1;
			break;
		case 1 : 
			ibuf[4] = 1; 
			ibuf[5] = 1; 
			break;
		case 2 :
			ibuf[0] = 1;
			for(i=2;i<4;i++) 
				ibuf[i] = 1;
			for(i=5;i<7;i++) 
				ibuf[i] = 1;
			break;
		case 3 :
			ibuf[0] = 1;
			for(i=3;i<7;i++) 
				ibuf[i] = 1;
			break;
		case 4 :
			ibuf[0] = 1;
			ibuf[1] = 1;
			for(i=4;i<6;i++) 
				ibuf[i] = 1;
			break;
		case 5 :
			for(i=0;i<2;i++) 
				ibuf[i] = 1;
			ibuf[3] = 1;
			ibuf[4] = 1;
			ibuf[6] = 1;
			break;
		case 6 :
			for (i=0;i<5;i++) 
				ibuf[i] = 1;
			ibuf[6] = 1;
			break;
		case 7 :
			ibuf[1] = 1;
			for (i=4;i<7;i++) 
				ibuf[i] = 1;
			break;
		case 8 :
			for (i=0; i<7; i++) 
				ibuf[i] = 1;
			break;
		case 9 :
			for (i=0; i<2; i++) 
				ibuf[i] = 1;
			for (i=3; i<7; i++) 
				ibuf[i] = 1;
			break;
	}
	return 0;
}
	
static ssize_t fnd_misc_driver_write(struct file * file, const char * buf, size_t length, loff_t * ofs){
	int ret,i,j;
	unsigned char cbuf[2];
	printk(KERN_INFO "fnd_misc_driver_write!\n");
	ret = copy_from_user(cbuf,buf,length);
	for(i=1;i>=0;i--){
		Getsegmentcode_base((unsigned int) cbuf[i]);
		for(j=0;j<8;j++){
			gpio_direction_output(LATCH_PIN,LOW);
			gpio_direction_output(CLOCK_PIN,LOW);
			gpio_direction_output(DATA_PIN,ibuf[j]);
			gpio_direction_output(CLOCK_PIN,HIGH);
			gpio_direction_output(LATCH_PIN,HIGH);
		}
	}
	return 0;
}	
	
static int fnd_misc_driver_open(struct inode * inode, struct file * file){
	int ret;
	printk(KERN_INFO "fnd_misc_driver_open!\n");
	ret = gpio_request(DATA_PIN,"fnd");
	if(ret<0)
		printk(KERN_INFO "fnd_misc_driver_open gpio_request failed!\n");
	gpio_direction_output(DATA_PIN,LOW);
	ret = gpio_request(LATCH_PIN,"fnd");
	if(ret<0)
		printk(KERN_INFO "fnd_misc_driver_open gpio_request failed!\n");
	gpio_direction_output(LATCH_PIN,LOW);
	ret = gpio_request(CLOCK_PIN,"fnd");
	if(ret<0)
		printk(KERN_INFO "fnd_misc_driver_open gpio_request failed!\n");
	gpio_direction_output(CLOCK_PIN,HIGH);
	return 0;
}

static int fnd_misc_driver_release(struct inode * inode, struct file * file){
	printk(KERN_INFO "fnd_misc_driver_release!\n");
	gpio_free(DATA_PIN);
	gpio_free(LATCH_PIN);
	gpio_free(CLOCK_PIN);
	return 0;
}

static struct file_operations fnd_misc_driver_fops = {
	.owner = THIS_MODULE,
	.open = fnd_misc_driver_open,
	.release = fnd_misc_driver_release,
	.write = fnd_misc_driver_write,
};

static struct miscdevice fnd_misc_driver_driver = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fnd_misc_driver",
	.fops = &fnd_misc_driver_fops,
};

static int fnd_misc_driver_init(void){
	printk(KERN_INFO "fnd_misc_driver_init!\n");
	return misc_register(&fnd_misc_driver_driver);
}

static void fnd_misc_driver_exit(void){
	printk(KERN_INFO "fnd_misc_driver_exit!\n");
	misc_deregister(&fnd_misc_driver_driver);	
}

module_init(fnd_misc_driver_init);
module_exit(fnd_misc_driver_exit);

MODULE_LICENSE("GPL");
