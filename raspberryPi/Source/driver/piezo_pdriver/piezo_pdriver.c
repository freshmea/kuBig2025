#include <linux/miscdevice.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <linux/uaccess.h>
#include <linux/pwm.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>

struct piezo {
	struct pwm_device *pwm;
	int pwm_id;
	int pwm_period_ns;
	int pwm_max;
	int pwm_default;
};

struct piezo *piezo;

#define PIEZO_PWM_CH 0
#define PERIOD_NS 38265       
#define DUTY_NS 1000*18       

static int period_table[] =
{
	956022, 902527, 851788, 803858,
	758725, 716332, 676132, 638162,
	602046, 568181, 536480, 506329,
	477783, 451059, 425713, 401767,
	379218, 358037, 337952, 318979,
	301023, 284090, 268168, 253100
};

static int piezo_open(struct inode * inode, struct file * file){
	printk("piezo_open, \n");
	return 0;
}

static int piezo_release(struct inode * inode, struct file * file){
	printk("piezo_release, \n");
	
	return 0;
}

static ssize_t piezo_write(struct file * file, const char * buf, size_t length, loff_t * ofs){
	printk("piezo_write, \n");
	
	int period;
	int ret;
	ret = copy_from_user(&period,buf,length);
	pwm_config(piezo->pwm,PERIOD_NS,period_table[period]);
	pwm_enable(piezo->pwm);
	mdelay(500);
	pwm_config(piezo->pwm,0,PERIOD_NS);
	
	return 0;
}

static struct file_operations piezo_fops = {
	.owner = THIS_MODULE,
	.open = piezo_open,
	.release = piezo_release,
	.write = piezo_write,
};

static struct miscdevice piezo_misc_driver = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "piezo",
	.fops = &piezo_fops,
};

static int piezo_parse_dt(struct platform_device *pdev, struct piezo *piezo)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
    	unsigned int rdata;

	dev->platform_data = piezo;
	if(of_property_read_u32(np, "pwm_id", &rdata))
		return -1;
	piezo->pwm_id = rdata;
	if(of_property_read_u32(np, "pwm_period_ns", &rdata))
		return -1;
	piezo->pwm_period_ns = rdata;
	if(of_property_read_u32(np, "pwm_max", &rdata))
		return -1;
	piezo->pwm_max = rdata;
	if(of_property_read_u32(np, "pwm_default", &rdata))
		return -1;
	piezo->pwm_default = rdata;
	return 0;
}

static int piezo_probe(struct platform_device *pdev)
{
	int ret = 0;
	piezo = devm_kzalloc(&pdev->dev, sizeof(*piezo), GFP_KERNEL);
	if (!piezo) {
		dev_err(&pdev->dev, "no memory for state\n");
		ret = -ENOMEM;
		goto err_alloc;
	}

	if (!pdev->dev.of_node) {
		ret = -ENODEV;
		dev_err(&pdev->dev, "failed to dev.of_node!\n");
		goto err_alloc;
	}

	if(piezo_parse_dt(pdev, piezo))  {
	ret = -ENODEV;
	dev_err(&pdev->dev, "failed to piezo_parse_dt!\n");
		goto err_alloc;
	}

	piezo->pwm = pwm_request(piezo->pwm_id, "piezo");
	if (IS_ERR(piezo->pwm)) {
		ret = -ENODEV;
		dev_err(&pdev->dev, "unable to request legacy PWM!\n");
		goto err_alloc;
	}

	pwm_config(piezo->pwm, piezo->pwm_period_ns * piezo->pwm_default / piezo->pwm_max, piezo->pwm_period_ns);
	pwm_enable(piezo->pwm);

	misc_register(&piezo_misc_driver);

	return 0;

err_alloc:
	return ret;
}

static int piezo_remove(struct platform_device *pdev)
{
	pwm_config(piezo->pwm,0,PERIOD_NS);
	pwm_disable(piezo->pwm);
	pwm_free(piezo->pwm);
	misc_deregister(&piezo_misc_driver);
	return 0;
}

static const struct of_device_id piezo_dt[] = {
	{ .compatible = "piezo" },
	{ },
};
MODULE_DEVICE_TABLE(of, piezo_dt);

static struct platform_driver piezo_driver = {
	.driver = {
		.name = "piezo",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(piezo_dt),
	},
	.probe 		= piezo_probe,
	.remove 	= piezo_remove,
};

static int __init piezo_init(void){
	printk("piezo_init, \n");
	return platform_driver_register(&piezo_driver);
}

static void __exit piezo_exit(void){
	printk("piezo_exit, \n");
	platform_driver_unregister(&piezo_driver);
}

module_init(piezo_init);
module_exit(piezo_exit);

MODULE_LICENSE("GPL");
