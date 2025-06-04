#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define GYRO_ADDR 0x68

// 자이로 센서 레지스트리 MPU6050
#define MPU6050_PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

// led 핀
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1
// buzzer
#define BUZZER_PIN 26

int doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

typedef struct
{
    int32_t accel_x_offset;
    int32_t accel_y_offset;
    int32_t accel_z_offset;
    int32_t gyro_x_offset;
    int32_t gyro_y_offset;
    int32_t gyro_z_offset;

} Gyro_offset;

typedef struct
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
} Gyro_data;

Gyro_offset init_gyro(int gyro_fd);
Gyro_data get_gyro(int gyro_fd);
void setPWMFrequency(int freq);

int main(void)
{
    // MPU 6050 I2C file descriptor
    int gyro_fd = wiringPiI2CSetup(GYRO_ADDR);
    delay(100);
    printf("test code1\n");
    wiringPiSetupGpio(); // BCM 기준 gpio 핀번호
    printf("test code2\n");
    int led[4] = {LED1, LED2, LED3, LED4};

    for (int i = 0; i < 4; ++i)
    {
        pinMode(led[i], OUTPUT);
    }
    pinMode(BUZZER_PIN, OUTPUT);
    printf("test code3-1\n");
    Gyro_offset offset = init_gyro(gyro_fd);
    Gyro_data data;
    printf("test code3\n");
    while (1)
    {
        data = get_gyro(gyro_fd);
        delay(100);
        printf("data.ax : %d\n", data.ax);
        if (data.ax - offset.accel_x_offset < 15000 || data.ax - offset.accel_x_offset < 17000)
        {
            for (int i = 0; i < 8; ++i)
            {
                printf("detect\n");
                setPWMFrequency(doReMi[i]);
                pwmWrite(BUZZER_PIN, 1000); // HIGH 가 유지되는 틱 수
                digitalWrite(led[i], HIGH);
                delay(100);
                digitalWrite(led[i], LOW);
                delay(100);
            }
        }
    }
    return 0;
}

Gyro_offset init_gyro(int gyro_fd)
{
    printf("test code4-1\n");
    // initiation MPU 6050
    wiringPiI2CWriteReg8(gyro_fd, MPU6050_PWR_MGMT_1, 0x00); // 슬립 모드 해제
    wiringPiI2CWriteReg8(gyro_fd, GYRO_CONFIG, 0x00);        // 자이로 범위 250 도/s
    wiringPiI2CWriteReg8(gyro_fd, ACCEL_CONFIG, 0x00);       // 가속도 범위 +-2g
    delay(100);

    const int samples = 100;

    Gyro_offset offset;
    printf("test code4\n");
    for (int i = 0; i < samples; i++)
    {
        int16_t ax = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 1);
        int16_t ay = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 3);
        int16_t az = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 5);
        int16_t gx = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 1);
        int16_t gy = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 3);
        int16_t gz = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 5);
        offset.accel_x_offset += ax;
        offset.accel_y_offset += ay;
        offset.accel_z_offset += az;
        offset.gyro_x_offset += gx;
        offset.gyro_y_offset += gy;
        offset.gyro_z_offset += gz;
        delay(10);
        printf("test code5\n");
    }
    offset.accel_x_offset /= 100;
    offset.accel_y_offset /= 100;
    offset.accel_z_offset /= 100;
    offset.gyro_x_offset /= 100;
    offset.gyro_y_offset /= 100;
    offset.gyro_z_offset /= 100;
    offset.accel_z_offset -= 16384.0;

    return offset;
}

Gyro_data get_gyro(int gyro_fd)
{
    Gyro_data data;
    data.ax = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 1);
    data.ay = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 3);
    data.az = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 5);
    data.gx = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 1);
    data.gy = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 3);
    data.gz = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 5);
    return data;
}

void setPWMFrequency(int freq)
{
    int range = 2000;
    int clock = 19200000 / (range * freq); // 19.2Mhz base clock
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range); // 클락을 나누는 틱의 갯수
    pwmSetClock(clock); // clock = 분주비 라고 생각해도 됨.
}
