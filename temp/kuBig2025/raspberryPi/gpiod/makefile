# sudo apt-get install libi2c-dev
# sudo apt-get install libgpiod-dev
TARGET = helloRaspberry switch_led interrupt led_pwm soft_tone_buzzer hard_tone_buzzer i2c_rgb_led i2c_rgb_led_switch i2c_servo
all : ${TARGET}
CFLAGS = -lgpiod -li2c -lpthread

% : %.c
	cc -o $@ $< ${CFLAGS}

clean :
	rm ${TARGET}
