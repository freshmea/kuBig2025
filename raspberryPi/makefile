TARGET = helloRaspberry switch_led interrupt led_pwm soft_tone_buzzer hard_tone_buzzer
all : ${TARGET}
CFLAGS = -lwiringPi

% : %.c
	cc -o $@ $< ${CFLAGS}

clean :
	rm ${TARGET}
