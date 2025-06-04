#include <errno.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

// PCA9685 설정
#define PCA9685_I2C_ADDR 0x5e // PCA9685 기본 I2C 주소
#define I2C_BUS "/dev/i2c-1"  // Raspberry Pi의 I2C 버스 (보통 1번)
#define PCA9685_MODE1 0x00    // Mode 1 레지스터
#define PCA9685_PRESCALE 0xFE // 주파수 설정 레지스터
#define LED0_ON_L 0x06        // LED0 (채널 0) 시작 레지스터

// 서보 펄스 폭 (마이크로초)
#define SERVO_MIN 500  // 0도
#define SERVO_MID 1500 // 90도
#define SERVO_MAX 2200 // 180도

// PCA9685 PWM 설정 상수
#define PWM_FREQ 50         // 서보 모터 주파수 (Hz)
#define OSC_FREQ 25000000   // PCA9685 내부 오실레이터 주파수 (25MHz)
#define PWM_RESOLUTION 4096 // 12비트 해상도

// I2C 장치 열기
int i2cOpen(const char *bus)
{
    int fd = open(bus, O_RDWR);
    if (fd < 0)
    {
        printf("I2C 버스 열기 실패: %s\n", strerror(errno));
        return -1;
    }
    return fd;
}

// I2C 장치에 쓰기
int i2cWriteByte(int fd, unsigned char addr, unsigned char reg, unsigned char data)
{
    struct i2c_msg messages[1];
    struct i2c_rdwr_ioctl_data packets;
    unsigned char buffer[2] = {reg, data};

    messages[0].addr = addr;
    messages[0].flags = 0; // 쓰기
    messages[0].len = 2;
    messages[0].buf = buffer;

    packets.msgs = messages;
    packets.nmsgs = 1;

    if (ioctl(fd, I2C_RDWR, &packets) < 0)
    {
        printf("I2C 쓰기 실패: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

// PCA9685 초기화
int pca9685Init(int fd)
{
    // MODE1: 리셋 및 설정 (Sleep 모드 진입)
    if (i2cWriteByte(fd, PCA9685_I2C_ADDR, PCA9685_MODE1, 0x10) < 0)
    {
        return -1;
    }
    usleep(5000); // 리셋 대기

    // 주파수 설정 (50Hz)
    int prescale = (int)((OSC_FREQ / (PWM_RESOLUTION * PWM_FREQ)) - 1);
    if (i2cWriteByte(fd, PCA9685_I2C_ADDR, PCA9685_PRESCALE, prescale) < 0)
    {
        return -1;
    }

    // MODE1: Sleep 해제 및 자동 증가 활성화
    if (i2cWriteByte(fd, PCA9685_I2C_ADDR, PCA9685_MODE1, 0xA1) < 0)
    {
        return -1;
    }
    usleep(5000); // 설정 적용 대기

    return 0;
}

// 서보 펄스 폭 설정
int setServoPulse(int fd, int channel, int pulseWidth)
{
    // 펄스 폭을 12비트 값으로 변환 (4096 단위)
    int onTime = 0; // 시작 시간 (0으로 고정)
    int offTime = (pulseWidth * PWM_RESOLUTION) / (1000000 / PWM_FREQ);

    if (offTime >= PWM_RESOLUTION)
        offTime = PWM_RESOLUTION - 1;

    // 레지스터 계산
    int regBase = LED0_ON_L + (4 * channel); // 각 채널은 4바이트씩 차지
    unsigned char data[4] = {
        onTime & 0xFF,        // ON_L
        (onTime >> 8) & 0xFF, // ON_H
        offTime & 0xFF,       // OFF_L
        (offTime >> 8) & 0xFF // OFF_H
    };

    struct i2c_msg messages[1];
    struct i2c_rdwr_ioctl_data packets;
    unsigned char buffer[5] = {regBase, data[0], data[1], data[2], data[3]};

    messages[0].addr = PCA9685_I2C_ADDR;
    messages[0].flags = 0; // 쓰기
    messages[0].len = 5;
    messages[0].buf = buffer;

    packets.msgs = messages;
    packets.nmsgs = 1;

    if (ioctl(fd, I2C_RDWR, &packets) < 0)
    {
        printf("서보 설정 실패 (채널 %d): %s\n", channel, strerror(errno));
        return -1;
    }
    return 0;
}

int main()
{
    int i2c_fd;

    // I2C 장치 열기
    i2c_fd = i2cOpen(I2C_BUS);
    if (i2c_fd < 0)
    {
        return 1;
    }

    // PCA9685 초기화
    if (pca9685Init(i2c_fd) < 0)
    {
        printf("PCA9685 초기화 실패\n");
        close(i2c_fd);
        return 1;
    }

    // 채널 3에 연결된 서보 테스트
    int channel = 3;

    printf("서보를 0도로 이동\n");
    setServoPulse(i2c_fd, channel, SERVO_MIN);
    sleep(1);

    printf("서보를 90도로 이동\n");
    setServoPulse(i2c_fd, channel, SERVO_MID);
    sleep(1);

    printf("서보를 180도로 이동\n");
    setServoPulse(i2c_fd, channel, SERVO_MAX);
    sleep(1);

    printf("서보를 90도로 복귀\n");
    setServoPulse(i2c_fd, channel, SERVO_MID);
    sleep(1);

    // 종료: 모든 채널 끄기
    printf("서보 정지\n");
    setServoPulse(i2c_fd, channel, 0);

    // 채널 4에 연결된 서보 테스트
    channel = 4;

    printf("서보를 0도로 이동\n");
    setServoPulse(i2c_fd, channel, SERVO_MIN);
    sleep(1);

    printf("서보를 90도로 이동\n");
    setServoPulse(i2c_fd, channel, SERVO_MID);
    sleep(1);

    printf("서보를 180도로 이동\n");
    setServoPulse(i2c_fd, channel, SERVO_MAX);
    sleep(1);

    printf("서보를 90도로 복귀\n");
    setServoPulse(i2c_fd, channel, SERVO_MID);
    sleep(1);

    // 종료: 모든 채널 끄기
    printf("서보 정지\n");
    setServoPulse(i2c_fd, channel, 0);

    // I2C 장치 닫기
    close(i2c_fd);

    return 0;
}