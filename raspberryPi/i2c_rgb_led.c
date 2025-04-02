#include <wiringPi.h>
#include <wiringPiI2C.h>

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

int main(void)
{
    int rgb_servo_fd = wiringPiI2CSetup(RGB_SERVO_I2C_ADDR);
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_MODE1, 0x80);    // 리셋
    delay(10);                                                  // 리셋 후 대기
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_PRESCALE, 0x79); // 주파수 60Hz 설정
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_MODE1, 0x20);

    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L, 0);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 2, 4095);
    delay(1000);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 2, 0);
    delay(1000);
    return 0;
}