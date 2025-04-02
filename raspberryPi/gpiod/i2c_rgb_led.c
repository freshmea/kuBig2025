#include <fcntl.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

#define I2C_DEV "/dev/i2c-1" // 라즈베리파이 I2C 디바이스 경로

void i2C_init(int fd, int freq);

int main(void)
{
    int i2c_fd;

    // I2C 장치 열기
    if ((i2c_fd = open(I2C_DEV, O_RDWR)) < 0)
    {
        perror("open I2C device");
        return 1;
    }

    // I2C 슬레이브 주소 설정
    if (ioctl(i2c_fd, I2C_SLAVE, RGB_SERVO_I2C_ADDR) < 0)
    {
        perror("I2C_SLAVE");
        close(i2c_fd);
        return 1;
    }

    // PCA9685 초기화
    i2C_init(i2c_fd, 0x79); // 50 Hz
    // 프리스케일 값 = (오실레이터 주파수 / (4096 * 원하는 주파수)) - 1
    // 25000000 / (4096 * (0x79 + 1))=50.028817
    srand(time(NULL)); // random 셋

    // LED 초기 설정
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L, 0);     // 빨간색
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 4, 0); // 녹색
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 8, 0); // 파란색

    // 빨간색
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 2, 4095);
    usleep(100000);
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 2, 0);
    usleep(100000);

    // 녹색
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 6, 4095);
    usleep(100000);
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 6, 0);
    usleep(100000);

    // 파란색
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 10, 4095);
    usleep(100000);
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 10, 0);
    usleep(100000);

    // 점점 밝아지는 코드
    for (int i = 0; i < 4096; ++i)
    {
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 2, i);
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 6, 4096 - i);
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 10, (i * 2) % 4096);
        usleep(1000);
    }

    // 랜덤한 색깔
    for (int i = 0; i < 100; ++i)
    {
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 2, rand() % 4096);
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 6, rand() % 4096);
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 10, rand() % 4096);
        usleep(100000);
    }

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