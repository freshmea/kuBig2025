#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/uaccess.h>

#define	PCA9685_CHIP_ADDR		0x5e
#define	PCA9685_REG_MODE1		0x00
#define	PCA9685_REG_MODE2		0x01
#define	PCA9685_REG_PRESCALE	0xFE
#define	PCA9685_REG_LED0_ON_L	0x06
#define	PCA9685_REG_LED0_ON_H	0x07
#define	PCA9685_REG_LED0_OFF_L	0x08
#define	PCA9685_REG_LED0_OFF_H	0x09
#define	PCA9685_REG_ALL_ON_L	0xFA
#define	PCA9685_REG_ALL_ON_H	0xFB
#define	PCA9685_REG_ALL_OFF_L	0xFC
#define	PCA9685_REG_ALL_OFF_H	0xFD

#define	RESTART	1<<7
#define	AI		1<<5
#define	SLEEP	1<<4
#define	ALLCALL	1<<0
#define	OCH		1<<3
#define	OUTDRV	1<<2
#define INVRT	1<<4

#define PCA9685_BASE    	0x57
#define SET_DUTY	_IO(PCA9685_BASE,0x31)
#define SET_FREQ	_IO(PCA9685_BASE,0x32)
#define SET_CHAN	_IO(PCA9685_BASE,0x33)

struct pca9685_sensor {
	struct i2c_client *client;
	struct device *dev;
};

static struct pca9685_sensor *pca9685_ptr;
int cur_channel = -1;

static void pca9685_set_duty(int percent){
	int step,on,off,temp; 
	char buf[4];
	step = percent * 4096;
	temp = step % 100;
	step = step / 100;
	if(temp > 49)
		step++;

	on = 0;
	off = step;
	buf[3] = on&0xff;
	buf[2] = on>>8;
	buf[1] = off&0xff;
	buf[0] = off>>8;
	if(cur_channel>=0){
		i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_LED0_ON_L+4*cur_channel,buf[3]);
		i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_LED0_ON_H+4*cur_channel,buf[2]);
		i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_LED0_OFF_L+4*cur_channel,buf[1]);
		i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_LED0_OFF_H+4*cur_channel,buf[0]);
	}
	else{
		i2c_smbus_write_block_data(pca9685_ptr->client,PCA9685_REG_ALL_ON_L,4,buf);
	}
}

static void pca9685_set_frequency(int freq){
	int prescale;
	char recv,buffer;
	prescale = (int)((25000000 / (4096 * freq))-1);
		
	if(prescale < 3)
		prescale = 3;
	else if(prescale > 255)
		prescale = 255;

	recv = i2c_smbus_read_byte_data(pca9685_ptr->client,PCA9685_REG_MODE1);
	buffer = (recv &(~SLEEP))|SLEEP;
	i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_MODE1,buffer);
	i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_PRESCALE,prescale);
	i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_MODE1,recv);
	udelay(500);
	buffer = recv | RESTART;
	i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_MODE1,buffer);
}

static int pca9685_open(struct inode * inode, struct file * file){
	char buffer,recv;
	printk(KERN_INFO "pca9685_open, \n");

	buffer = AI|ALLCALL;
	i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_MODE1,buffer);
	buffer = OCH|OUTDRV;
	i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_MODE2,buffer);
	udelay(500);
	recv = i2c_smbus_read_byte_data(pca9685_ptr->client,PCA9685_REG_MODE1);
	buffer = recv &(~SLEEP);
	i2c_smbus_write_byte_data(pca9685_ptr->client,PCA9685_REG_MODE1,buffer);
	udelay(500);
	pca9685_set_duty(0);
	udelay(500);
	pca9685_set_frequency(200);
	
	return 0;
}

static int pca9685_release(struct inode * inode, struct file * file){
	printk(KERN_INFO "pca9685_release, \n");
	return 0;
}

static long pca9685_ioctl(struct file *file,unsigned int cmd, long unsigned int arg){
	printk(KERN_INFO "pca9685_ioctl\n");
	switch(cmd) {
		case SET_DUTY:
			pca9685_set_duty(arg);
			break;
		break;
		case SET_FREQ:
			pca9685_set_frequency(arg);
			break;
		case SET_CHAN:
			cur_channel = arg;
			break;
	}
	return 0;
}

static struct file_operations pca9685_fops = {
	.owner			= THIS_MODULE,
	.open			= pca9685_open,
	.unlocked_ioctl	= pca9685_ioctl,
	.release		= pca9685_release,
};

static struct miscdevice pca9685_driver = {
	.fops	= &pca9685_fops,
	.name	= "pca9685_test",
	.minor	= MISC_DYNAMIC_MINOR,
};

static int pca9685_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct pca9685_sensor *sensor;
	int error;
	printk(KERN_INFO "pca9685_probe, \n");
	sensor = kzalloc(sizeof(struct pca9685_sensor), GFP_KERNEL);

	if(!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
	{
		error = -ENODEV;
		goto err_free_mem;
	}
	sensor->client = client;
	sensor->dev = &client->dev;
	sensor->client->addr = PCA9685_CHIP_ADDR;

	i2c_set_clientdata(client,sensor);
	pca9685_ptr = sensor;
	error = misc_register(&pca9685_driver);
	if (error) {
		dev_err(&client->dev, "failed to register input device\n");
		goto err_mpuirq_failed;
	}
	return 0;

err_mpuirq_failed:
	misc_deregister(&pca9685_driver);

err_free_mem:
	kfree(sensor);

	return error;
}

static int pca9685_remove(struct i2c_client *client){
	printk(KERN_INFO "pca9685_remove, \n");
	misc_deregister(&pca9685_driver);
	return 0;
}

static const struct i2c_device_id pca9685_ids[] = {
	{ "pca9685_test", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, pca9685_ids);

static struct i2c_driver pca9685_i2c_driver = {
	.driver = {
		.name   = "pca9685_test",
		.owner  = THIS_MODULE,
	},
	.probe          = pca9685_probe,
	.remove         = pca9685_remove,
	.id_table       = pca9685_ids,
};

static int pca9685_init(void){
	printk(KERN_INFO "pca9685_init, \n");
	return i2c_add_driver(&pca9685_i2c_driver);
}

static void pca9685_exit(void){
	printk(KERN_INFO "pca9685_exit, \n");
	i2c_del_driver(&pca9685_i2c_driver);
}

module_init(pca9685_init);
module_exit(pca9685_exit);

MODULE_LICENSE("GPL");