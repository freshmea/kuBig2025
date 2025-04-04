TARGET = gyro_cnt
# temp_humi
# helloRaspberry switch_led interrupt led_pwm soft_tone_buzzer hard_tone_buzzer i2c_rgb_led i2c_rgb_led_switch i2c_servo device_gpio fnd_cnt rgb_switch_fnd pir_cnt touch_ATQT1070
# driver_exam_native device_gpio led_driver_native led_switch_driver_native switch_driver_native
all : ${TARGET}
CFLAGS = -lwiringPi

% : %.c
	cc -o $@ $< ${CFLAGS}

clean :
	rm ${TARGET}
