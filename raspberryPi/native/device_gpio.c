#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// phys pin
#define LED1 535

int main(void)
{
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "535", strlen("535"));
    close(fd);
    fd = open("/sys/class/gpio/gpio535/direction", O_WRONLY);
    write(fd, "out", strlen("out"));
    close(fd);
    fd = open("/sys/class/gpio/gpio535/value", O_WRONLY);
    for (int i = 0; i < 5; ++i)
    {
        write(fd, "1", strlen("1"));
        sleep(1);
        write(fd, "0", strlen("0"));
        sleep(1);
    }
    close(fd);
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    write(fd, "535", strlen("535"));
    close(fd);
    return 0;
}