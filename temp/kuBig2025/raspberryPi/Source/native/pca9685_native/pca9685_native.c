#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <sys/ioctl.h>

#define PCA9685_BASE    	0x57
#define SET_DUTY	_IO(PCA9685_BASE,0x31)
#define SET_FREQ	_IO(PCA9685_BASE,0x32)
#define SET_CHAN	_IO(PCA9685_BASE,0x33)

int main(int argc, char * argv[]) {
	int dev,i;
	int ret=0,data=0;
	double scale=0,freq=50;

	dev = open("/dev/pca9685_test", O_WRONLY);	
	ioctl(dev,SET_FREQ,50);
	
	while(1){
		ioctl(dev,SET_CHAN,0);
		for(i=0;i<=100;i++){
			ioctl(dev,SET_DUTY,i);
			usleep(100000);
		}
		ioctl(dev,SET_CHAN,1);
		for(i=0;i<=100;i++){
			ioctl(dev,SET_DUTY,i);
			usleep(100000);
		}
		ioctl(dev,SET_CHAN,2);
		for(i=0;i<=100;i++){
			ioctl(dev,SET_DUTY,i);
			usleep(100000);
		}
		ioctl(dev,SET_CHAN,3);
		for(i=3;i<=13;i++){
			ioctl(dev,SET_DUTY,i);
			usleep(500000);
		}
		ioctl(dev,SET_CHAN,4);
		for(i=3;i<=13;i++){
			ioctl(dev,SET_DUTY,i);
			usleep(500000);
		}
	}
	close(dev);	
	

	return 0;
}
