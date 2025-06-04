#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
	int dev,i;
	char buf[2]={0,0};
	dev = open("/dev/fnd_misc_driver",O_RDWR);
	if(dev<0){
		printf("driver open failed!\n");
		return -1;
	}
	for(i=99;i>=0;i--){
		buf[0]=i/10;
		buf[1]=i%10;
		write(dev,&buf,2);
		sleep(1);
	}
	close(dev);
	return 0;
}
