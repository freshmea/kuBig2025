#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
	int dev,i,flag=1;

	dev = open("/dev/piezo", O_WRONLY);

	while(flag)
	{
		printf("input number(0~23, exit=100): ");
		scanf("%d",&i);
		if(i>=0 && i<23)
			write(dev,&i,sizeof(i));
		else if(i==100)
			flag=0;
		else
			printf("wrong number\n");
	}

	close(dev);

	return 0;
}
