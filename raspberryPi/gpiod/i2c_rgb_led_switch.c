#include <fcntl.h>
#include <gpiod.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

#define I2C_DEV "/dev/i2c-1"  // 라즈베리파이 I2C 디바이스 경로
#define CHIP_NAME "gpiochip0" // GPIO 칩 이름

#define SW1 4
#define SW2 17
#define SW3 27
#define SW4 22

#define CONSUMER "rgb_led_switch_app"

void i2C_init(int fd, int freq);
void *switch_monitor_thread(void *arg);

// 색상 값 저장 전역 변수
int r_value = 0, g_value = 0, b_value = 0;
int r_start_time = 0, g_start_time = 0, b_start_time = 0;
int r_pushed = 0, g_pushed = 0, b_pushed = 0;

// I2C 파일 디스크립터 저장 전역 변수
int i2c_fd;

int main(void)
{
    struct gpiod_chip *chip;
    struct gpiod_line *sw_lines[4];
    int sw[4] = {SW1, SW2, SW3, SW4};
    pthread_t switch_thread;

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

    // LED 초기 설정
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L, 0);     // 빨간색
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 4, 0); // 녹색
    i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 8, 0); // 파란색

    // gpiod 칩 열기
    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip)
    {
        perror("gpiod_chip_open_by_name");
        close(i2c_fd);
        return 1;
    }

    // 스위치 핀 설정
    for (int i = 0; i < 4; ++i)
    {
        sw_lines[i] = gpiod_chip_get_line(chip, sw[i]);
        if (!sw_lines[i])
        {
            perror("gpiod_chip_get_line");
            gpiod_chip_close(chip);
            close(i2c_fd);
            return 1;
        }

        if (gpiod_line_request_input(sw_lines[i], CONSUMER) < 0)
        {
            perror("gpiod_line_request_input");
            gpiod_chip_close(chip);
            close(i2c_fd);
            return 1;
        }
    }

    // 스위치 모니터링 스레드 시작
    if (pthread_create(&switch_thread, NULL, switch_monitor_thread, sw_lines) != 0)
    {
        perror("pthread_create");
        for (int i = 0; i < 4; ++i)
        {
            gpiod_line_release(sw_lines[i]);
        }
        gpiod_chip_close(chip);
        close(i2c_fd);
        return 1;
    }

    // 메인 루프: RGB LED 업데이트
    while (1)
    {
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 2, r_value);
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 6, g_value);
        i2c_smbus_write_word_data(i2c_fd, PCA9685_LED_ON_L + 10, b_value);
        usleep(10000); // 10ms 대기
    }

    // 자원 해제 (여기까지 도달하지 않지만 완전성을 위해 포함)
    pthread_join(switch_thread, NULL);
    for (int i = 0; i < 4; ++i)
    {
        gpiod_line_release(sw_lines[i]);
    }
    gpiod_chip_close(chip);
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

void *switch_monitor_thread(void *arg)
{
    struct gpiod_line **sw_lines = (struct gpiod_line **)arg;

    // 스위치 모니터링 루프
    while (1)
    {
        // SW1: R 색상 변경
        if (gpiod_line_get_value(sw_lines[0]))
        {
            if (!r_pushed)
            {
                r_start_time = clock() / (CLOCKS_PER_SEC / 1000); // 밀리초로 변환
                r_pushed = 1;
            }
        }
        else if (r_pushed)
        {
            int press_time = clock() / (CLOCKS_PER_SEC / 1000) - r_start_time;
            r_value = (press_time * 4095 / 1000);
            if (r_value >= 4096)
                r_value = 4095;
            printf("R: %d\n", r_value);
            r_pushed = 0;
        }

        // SW2: G 색상 변경
        if (gpiod_line_get_value(sw_lines[1]))
        {
            if (!g_pushed)
            {
                g_start_time = clock() / (CLOCKS_PER_SEC / 1000);
                g_pushed = 1;
            }
        }
        else if (g_pushed)
        {
            int press_time = clock() / (CLOCKS_PER_SEC / 1000) - g_start_time;
            g_value = (press_time * 4095 / 1000);
            if (g_value >= 4096)
                g_value = 4095;
            printf("G: %d\n", g_value);
            g_pushed = 0;
        }

        // SW3: B 색상 변경
        if (gpiod_line_get_value(sw_lines[2]))
        {
            if (!b_pushed)
            {
                b_start_time = clock() / (CLOCKS_PER_SEC / 1000);
                b_pushed = 1;
            }
        }
        else if (b_pushed)
        {
            int press_time = clock() / (CLOCKS_PER_SEC / 1000) - b_start_time;
            b_value = (press_time * 4095 / 1000);
            if (b_value >= 4096)
                b_value = 4095;
            printf("B: %d\n", b_value);
            b_pushed = 0;
        }

        usleep(10000); // 10ms 대기
    }

    return NULL;
}