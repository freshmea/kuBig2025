#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

#define I2C_DEV "/dev/i2c-1"  // 라즈베리파이 I2C 디바이스 경로

void i2C_init(int fd, int freq);

int main(void)
{
    int i2c_fd;
    
    // I2C 장치 열기
    if ((i2c_fd = open(I2C_DEV, O_RDWR)) < 0) {
        perror("open I2C device");
        return 1;
    }
    
    // I2C 슬레이브 주소 설정
    if (ioctl(i2c_fd, I2C_SLAVE, RGB_SERVO_I2C_ADDR) < 0) {
        perror("I2C_SLAVE");
        close(i2c_fd);
        return 1;
    }
    
    // PCA9685 초기화
    i2C_init(i2c_fd, 0x79); // 50 Hz (20ms)
    
    int servo_0 = 120;
    int servo_180 = 500;
    
    // Servo1 설정 (0도)
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 12, 0);       // servo1 on_off
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 14, servo_0); // servo1 pwm duty
    usleep(10000);
    
    // Servo2 설정 (0도)
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 16, 0);       // servo2
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 18, servo_0); // servo2 pwm duty
    sleep(1);
    printf("set \n");
    
    // 90도로 이동
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 14, servo_180 / 2); // servo1 pwm duty
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 18, servo_180 / 2); // servo2 pwm duty
    sleep(1);
    printf("set 90\n");
    
    // 180도로 이동
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 14, servo_180); // servo1 pwm duty
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 18, servo_180); // servo2 pwm duty
    sleep(1);
    printf("set 180\n");
    
    // free 상태로 설정
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 14, 0); // servo1 pwm duty
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 18, 0); // servo2 pwm duty
    
    close(i2c_fd);
    return 0;
}

void i2C_init(int fd, int freq)
{
    // PCA9685 초기화
    i2c_smbus_write_byte_data(fd, PCA9685_MODE1, 0x10);    // 리셋
    usleep(10000);                                         // 리셋 후 대기
    i2c_smbus_write_byte_data(fd, PCA9685_PRESCALE, freq); // 주파수 설정
    i2c_smbus_write_byte_data(fd, PCA9685_MODE1, 0xA1);    // Auto-Increment enable, Normal mode
}