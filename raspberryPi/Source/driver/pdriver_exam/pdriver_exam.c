#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/of_gpio.h>

static int pdriver_probe(struct platform_device *pdev)
{
	printk(KERN_INFO "pdriver_probe!\n");
	return 0;
}

static int pdriver_remove(struct platform_device *pdev)
{
	printk(KERN_INFO "pdriver_remove!\n");
	return 0;
}

static const struct of_device_id pdriver_dt[] = {
	{ .compatible = "pdriver" },
	{ },
};
MODULE_DEVICE_TABLE(of, pdriver_dt);

static struct platform_driver pdriver_driver = {
	.driver = {
		.name = "pdriver",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(pdriver_dt),
	},
	.probe 		= pdriver_probe,
	.remove 	= pdriver_remove,
};

static int __init pdriver_init(void){
	printk(KERN_INFO "pdriver_init!\n");
	return platform_driver_register(&pdriver_driver);
}

static void __exit pdriver_exit(void){
	printk(KERN_INFO "pdriver_exit!\n");
	platform_driver_unregister(&pdriver_driver);
}

module_init(pdriver_init);
module_exit(pdriver_exit);

MODULE_LICENSE("GPL");
