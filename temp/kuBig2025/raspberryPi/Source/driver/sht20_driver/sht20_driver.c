#include <linux/platform_device.h>
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
#include <linux/ioport.h>

#define SHT20_CHIP_ADREESS_WRITE 0x40
#define SHT20_CHIP_ADREESS_READ 0x81
#define SHT20_CHIP_TRIGGER_T_M 0xE3
#define SHT20_CHIP_TRIGGER_RH_M 0xE5
#define SHT20_CHIP_TRIGGER_T_N 0xF3
#define SHT20_CHIP_TRIGGER_RH_N 0xF5
#define SHT20_SOFT_RESET 0xFE

struct sht20_sensor {
        struct i2c_client *client;
        struct device *dev;
};

static struct sht20_sensor *sht20_ptr;

static void sht20_read_sensor(struct i2c_client *client, u8 *buffer, int length)
{
  int ret;
  char cmd;
  struct i2c_msg msg[] = {
		  {
			  .addr = SHT20_CHIP_ADREESS_WRITE,
			  .flags = 0,
			  .len = 1,
			  .buf = &cmd,
		  },
		  {
			  .addr = SHT20_CHIP_ADREESS_WRITE,
			  .flags = I2C_M_RD,
			  .len = 2,
			  .buf = buffer,
		  },
  };
  switch(length)
  {
    case 0:
      cmd = SHT20_CHIP_TRIGGER_T_M;
      break;
    case 1:
      cmd = SHT20_CHIP_TRIGGER_RH_M;
      break;
    case 3:
      cmd = SHT20_CHIP_TRIGGER_T_N;
      break;
    case 4:
      cmd = SHT20_CHIP_TRIGGER_RH_N;
      break;
  }
 
  ret  = i2c_transfer(client->adapter, msg, 2);
}

static int sht20_softReset(struct i2c_client *client)
{

  char cmd = SHT20_SOFT_RESET;

  struct i2c_msg msg[] = {
		  {
			  .addr = SHT20_CHIP_ADREESS_WRITE,
			  .flags = 0,
			  .len = 1,
			  .buf = &cmd,
		  }
  };

  i2c_transfer(client->adapter, msg, 1);
  return 0;
}

static int sht20_open(struct inode * inode, struct file * file){
	struct sht20_sensor *sensor;
	sensor = sht20_ptr;

	sht20_softReset(sensor->client);

	return 0;
}

static int sht20_release(struct inode * inode, struct file * file){
	printk("sht20_release, \n");
	return 0;
}

static DEFINE_MUTEX(sht20_mutex);
static long sht20_ioctl(struct file *file,unsigned int cmd, long unsigned int cData){
	u8 buffer[3];
	u16 sht20_buffer[3];
	int sht_sensor_value;
	struct sht20_sensor *sensor;
	sensor = sht20_ptr;

	sht20_read_sensor(sensor->client, (u8 *)buffer, cmd);

	sht20_buffer[0] = buffer[0]*256;
	sht20_buffer[1] = buffer[1] >> 2;

	sht_sensor_value = sht20_buffer[0] + sht20_buffer[1];

	return sht_sensor_value;
}

static struct file_operations sht20_fops = {
	.owner    = THIS_MODULE,
	.open    = sht20_open,
	.unlocked_ioctl  = sht20_ioctl,
	.release  = sht20_release,
};

static struct miscdevice sht20_driver = {
	.fops  = &sht20_fops,
	.name  = "sht20",
	.minor   = MISC_DYNAMIC_MINOR,
};

static int sht20_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct sht20_sensor *sensor;
	int error;

	sensor = kzalloc(sizeof(struct sht20_sensor), GFP_KERNEL);

	if(!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
	{
		error = -ENODEV;
		goto err_free_mem;
	}
	sensor->client = client;
	sensor->dev = &client->dev;

	i2c_set_clientdata(client,sensor);
	sht20_ptr = sensor;

	error = misc_register(&sht20_driver);
	if (error) {
		dev_err(&client->dev, "failed to register input device\n");
		goto err_mpuirq_failed;
	}
	return 0;

err_mpuirq_failed:
	misc_deregister(&sht20_driver);

err_free_mem:
	kfree(sensor);

	return error;
}

static int sht20_remove(struct i2c_client *client)
{
	misc_deregister(&sht20_driver);
	return 0;
}

static const struct i2c_device_id sht20_ids[] = {
       { "sht20", 0 },
       { }
};
MODULE_DEVICE_TABLE(i2c, sht20_ids);

static struct i2c_driver sht20_i2c_driver = {
	.driver = {
		.name   = "sht20",
		.owner  = THIS_MODULE,
	},
	.probe          = sht20_probe,
	.remove         = sht20_remove,
	.id_table       = sht20_ids,
};

static int sht20_init(void){
	return i2c_add_driver(&sht20_i2c_driver);
}

static void sht20_exit(void){
	i2c_del_driver(&sht20_i2c_driver);
}

module_init(sht20_init);
module_exit(sht20_exit);

MODULE_LICENSE("GPL");