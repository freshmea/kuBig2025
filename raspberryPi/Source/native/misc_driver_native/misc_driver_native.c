#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int dev;
	char buf=1;
	dev = open("/dev/misc_driver",O_RDWR);
	if(dev<0){
		printf("driver open failed!\n");
		return -1;
	}
	write(dev,&buf,1);
	read(dev,&buf,1);
	ioctl(dev,&buf,1);
	close(dev);
	return 0;
}
