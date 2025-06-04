#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ssd1306_i2c.h"

static volatile int keepRunning = 1;

void intHandler(int sig) {
    keepRunning = 0;
}

int main(int argc, char* argv[])
{
    signal(SIGINT, intHandler);

    int fd; 
    fd = ssd1306I2CSetup(0x3C);  
    displayOn(fd); 

    while(keepRunning) {
        draw_line(1, 1, "hello");
        draw_line(2, 1, "world");
        updateDisplay(fd);
        sleep(1);
        clearDisplay(fd);
    }

    clearDisplay(fd);
    draw_line(2, 1, "off in 2 sec");
    updateDisplay(fd);
    sleep(2);
    displayOff(fd);

    return 0;
}
