TARGET = helloRaspberry switch_led interrupt led_pwm
all : ${TARGET}
CFLAGS = -lwiringPi

% : %.c
	cc -o $@ $< ${CFLAGS}

clean :
	rm ${TARGET}
