// cc -o device_test device_test.c -lwiringPi

#include "ssd1306_i2c.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// 핀 정의 (BCM 번호 사용)
#define LED1_PIN 23
#define LED2_PIN 24
#define LED3_PIN 25
#define LED4_PIN 1
#define SW1_PIN 4
#define SW2_PIN 17
#define SW3_PIN 27
#define SW4_PIN 22
#define PIR_PIN 7
#define BUZZER_PIN 12

// 74HC595 핀 정의
#define DATA_PIN 0  // DS (직렬 데이터)
#define LATCH_PIN 5 // ST_CP (래치)
#define CLOCK_PIN 6 // SH_CP (클럭)

// I2C 장치 주소
#define TOUCH_I2C_ADDR 0x1b
#define TOUCH_READ_REG 0x03
#define TEMP_HUMID_I2C_ADDR 0x40
#define TEMP_HUMID_TRIG_TEMP_M 0xE3
#define TEMP_HUMID_TRIG_HUMID_M 0xE5
#define TEMP_HUMID_RESET 0xFE
#define GYRO_I2C_ADDR 0x68
#define RGB_SERVO_I2C_ADDR 0x5e
#define OLED_I2C_ADDR 0x3c

// 자이로 설정 레지스터
#define PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

// MPU6050 레지스터 (Gyro)
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_ACCEL_XOUT_H 0x3B

// PCA9685 레지스터 (RGB, Servo)
#define PCA9685_MODE1 0x00
#define PCA9685_PRESCALE 0xFE
#define PCA9685_LED0_ON_L 0x06

// 숫자별 세그먼트 패턴 (0~9, 공통 cathode 기준, a~g + dp)
unsigned char fndPatterns[] =
    {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
//     {
//         0b00000001, // 없음
//         0b00000010, // A
//         0b00000100, // B
//         0b00001000, // C
//         0b00010000, // D
//         0b00100000, // E
//         0b01000000, // F
//         0b10000000, // G
// };

// 함수 프로토타입 선언
void testLED(void);
void testSwitch(void);
void testPIR(void);
void testBuzzer(void);
void testTouchSensor(int touch_fd);
void testTempHumid(int temp_humid_fd);
void shiftOut16(unsigned char digit1, unsigned char digit2);
void testFND();
void testGyro(int gyro_fd);
void testRGB(int rgb_servo_fd);
void testServo(int rgb_servo_fd);
void testOLED(int oled_fd);
void testAll(int touch_fd, int temp_humid_fd, int gyro_fd, int fnd_fd, int rgb_servo_fd, int oled_fd);
void displayMenu(void);

int main(void)
{
    // WiringPi 초기화
    if (wiringPiSetupGpio() == -1)
    {
        printf("WiringPi 초기화 실패!\n");
        return 1;
    }

    // I2C 장치 초기화
    int touch_fd = wiringPiI2CSetup(TOUCH_I2C_ADDR);
    int temp_humid_fd = wiringPiI2CSetup(TEMP_HUMID_I2C_ADDR);
    int gyro_fd = wiringPiI2CSetup(GYRO_I2C_ADDR);
    int rgb_servo_fd = wiringPiI2CSetup(RGB_SERVO_I2C_ADDR);
    int oled_fd = wiringPiI2CSetup(OLED_I2C_ADDR);
    if (touch_fd == -1 || temp_humid_fd == -1 || gyro_fd == -1 || rgb_servo_fd == -1 || oled_fd == -1)
    {
        printf("I2C 장치 초기화 실패!\n");
        return 1;
    }

    // 핀 모드 설정
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
    pinMode(SW1_PIN, INPUT);
    pinMode(SW2_PIN, INPUT);
    pinMode(SW3_PIN, INPUT);
    pinMode(SW4_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    // 스위치 풀다운 저항 설정
    pullUpDnControl(SW1_PIN, PUD_DOWN);
    pullUpDnControl(SW2_PIN, PUD_DOWN);
    pullUpDnControl(SW3_PIN, PUD_DOWN);
    pullUpDnControl(SW4_PIN, PUD_DOWN);

    int choice = 0;
    char buffer[10];

    while (1)
    {
        displayMenu();
        printf("테스트할 장치 번호를 선택하세요 (0 입력시 종료): ");
        fgets(buffer, sizeof(buffer), stdin);
        choice = atoi(buffer);

        switch (choice)
        {
        case 0:
            printf("테스트를 종료합니다.\n");
            return 0;
        case 1:
            testLED();
            break;
        case 2:
            testSwitch();
            break;
        case 3:
            testPIR();
            break;
        case 4:
            testBuzzer();
            break;
        case 5:
            testTouchSensor(touch_fd);
            break;
        case 6:
            testTempHumid(temp_humid_fd);
            break;
        case 7:
            testFND();
            break;
        case 8:
            testGyro(gyro_fd);
            break;
        case 9:
            testRGB(rgb_servo_fd);
            break;
        case 10:
            testServo(rgb_servo_fd);
            break;
        case 11:
            testOLED(oled_fd);
            break;
        // case 12:
        //     testAll(touch_fd, temp_humid_fd, gyro_fd, rgb_servo_fd, oled_fd);
        //     break;
        default:
            printf("잘못된 선택입니다. 다시 선택해주세요.\n");
            break;
        }

        printf("\n아무 키나 누르면 메뉴로 돌아갑니다...\n");
        getchar(); // 엔터키 처리
    }

    return 0;
}

void displayMenu(void)
{
    printf("\n=== 장치 테스트 메뉴 ===\n");
    printf("1. LED 테스트\n");
    printf("2. 스위치 테스트\n");
    printf("3. PIR 센서 테스트\n");
    printf("4. 부저 테스트\n");
    printf("5. 터치 센서 테스트\n");
    printf("6. 온습도 센서 테스트\n");
    printf("7. FND 테스트\n");
    printf("8. Gyro 테스트\n");
    printf("9. RGB 테스트\n");
    printf("10. 서보 테스트\n");
    printf("11. OLED 테스트\n");
    printf("12. 모든 장치 테스트\n");
    printf("0. 종료\n");
}

void testLED(void)
{
    printf("LED 테스트: 모든 LED가 2초 동안 켜짐\n");
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);
    digitalWrite(LED4_PIN, HIGH);
    delay(2000);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(LED4_PIN, LOW);
    printf("LED 꺼짐 - LED가 깜빡였다면 정상\n");
}

void testSwitch(void)
{
    printf("스위치 테스트: 각 스위치를 누르면 메시지가 출력됩니다 (5초간 대기)\n");
    printf("(테스트 도중 종료하려면 Ctrl+C를 누르세요)\n");

    for (int i = 0; i < 50; i++)
    {
        if (digitalRead(SW1_PIN) == HIGH)
            printf("SW1 눌림 - SW1 정상\n");
        if (digitalRead(SW2_PIN) == HIGH)
            printf("SW2 눌림 - SW2 정상\n");
        if (digitalRead(SW3_PIN) == HIGH)
            printf("SW3 눌림 - SW3 정상\n");
        if (digitalRead(SW4_PIN) == HIGH)
            printf("SW4 눌림 - SW4 정상\n");
        delay(100);
    }
    printf("스위치 테스트 종료\n");
}

void testPIR(void)
{
    printf("PIR 센서 테스트: 움직임을 감지하면 메시지가 출력됩니다 (5초간 대기)\n");
    for (int i = 0; i < 50; i++)
    {
        if (digitalRead(PIR_PIN) == HIGH)
        {
            printf("PIR 센서: 움직임 감지 - PIR 정상\n");
        }
        delay(100);
    }
    printf("PIR 테스트 종료\n");
}

void testBuzzer(void)
{
    printf("부저 테스트: PWM으로 소리 발생 (도-레-미 음계)\n");

    // 도 (261Hz, C4)
    printf("도(C4) 연주 중...\n");
    for (int i = 0; i < 261; i++)
    {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(1915 / 2); // 주기 1915us (261Hz)
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(1915 / 2);
    }
    delay(500);

    // 레 (293Hz, D4)
    printf("레(D4) 연주 중...\n");
    for (int i = 0; i < 293; i++)
    {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(1706 / 2); // 주기 1706us (293Hz)
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(1706 / 2);
    }
    delay(500);

    // 미 (329Hz, E4)
    printf("미(E4) 연주 중...\n");
    for (int i = 0; i < 329; i++)
    {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(1520 / 2); // 주기 1520us (329Hz)
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(1520 / 2);
    }

    printf("부저에서 도-레-미 음계가 들렸다면 정상\n");
}

void testTouchSensor(int touch_fd)
{
    printf("터치 센서 테스트: 터치 상태 읽기 (5초간)\n");
    printf("(터치해 보세요)\n");

    for (int i = 0; i < 50; i++)
    {
        int touch_value = wiringPiI2CReadReg8(touch_fd, TOUCH_READ_REG);
        if (touch_value >= 0)
        {
            printf("터치 센서 값: %d - 터치 센서 정상 (터치 시 값 변화 확인)\n", touch_value);
        }
        else
        {
            printf("터치 센서 읽기 실패\n");
        }
        delay(100);
    }
    printf("터치 센서 테스트 종료\n");
}

void testTempHumid(int temp_humid_fd)
{
    printf("온습도 센서 테스트: 리셋 후 온도와 습도 측정\n");

    // 센서 리셋
    wiringPiI2CWrite(temp_humid_fd, TEMP_HUMID_RESET);
    delay(100); // 리셋 후 대기

    // 온도 측정 (M 모드)
    wiringPiI2CWrite(temp_humid_fd, TEMP_HUMID_TRIG_TEMP_M);
    delay(100);                                    // 최대 85ms 대기
    int temp_msb = wiringPiI2CRead(temp_humid_fd); // MSB 읽기
    int temp_lsb = wiringPiI2CRead(temp_humid_fd); // LSB 읽기

    if (temp_msb >= 0 && temp_lsb >= 0)
    {
        int temp_raw = (temp_msb << 8) | (temp_lsb & 0xFC); // 하위 2비트 제거
        float temperature = -46.85 + 175.72 * (temp_raw / 65536.0);
        printf("온도: %.2f°C - 온도 센서 정상\n", temperature);
    }
    else
    {
        printf("온도 읽기 실패: MSB=%d, LSB=%d\n", temp_msb, temp_lsb);
    }

    // 습도 측정 (M 모드)
    wiringPiI2CWrite(temp_humid_fd, TEMP_HUMID_TRIG_HUMID_M);
    delay(100);                                     // 최대 29ms 대기
    int humid_msb = wiringPiI2CRead(temp_humid_fd); // MSB 읽기
    int humid_lsb = wiringPiI2CRead(temp_humid_fd); // LSB 읽기

    if (humid_msb >= 0 && humid_lsb >= 0)
    {
        int humid_raw = (humid_msb << 8) | (humid_lsb & 0xFC); // 하위 2비트 제거
        float humidity = -6.0 + 125.0 * (humid_raw / 65536.0);
        printf("습도: %.2f%% - 습도 센서 정상\n", humidity);
    }
    else
    {
        printf("습도 읽기 실패: MSB=%d, LSB=%d\n", humid_msb, humid_lsb);
    }
}

// 74HC595로 16비트 데이터 전송 함수
void shiftOut16(unsigned char digit1, unsigned char digit2)
{
    unsigned short data = (digit1 << 9) | (digit2 << 1); // 16비트 데이터 생성 (digit1: MSB, digit2: LSB)

    // 16비트 전송
    for (int i = 15; i >= 0; i--)
    {
        digitalWrite(LATCH_PIN, LOW);            // Latch LOW
        digitalWrite(CLOCK_PIN, LOW);            // Clock LOW
        digitalWrite(DATA_PIN, (data >> i) & 1); // Data HIGH/LOW
        digitalWrite(CLOCK_PIN, HIGH);           // Clock HIGH
        digitalWrite(LATCH_PIN, HIGH);           // Latch HIGH
        delayMicroseconds(10);                   // CLOCK HIGH 유지 시간 확보
    }
    digitalWrite(LATCH_PIN, HIGH);
    delayMicroseconds(10);        // LATCH HIGH 유지 시간 확보
    digitalWrite(LATCH_PIN, LOW); // 최종 Latch LOW로 초기화
}
// FND 테스트 함수
void testFND()
{
    printf("FND 테스트: 단계별 확인 (각 2초간)\n");

    // GPIO 초기화
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);

    digitalWrite(DATA_PIN, LOW);
    digitalWrite(LATCH_PIN, LOW);
    digitalWrite(CLOCK_PIN, LOW);

    // 테스트 1: 첫 번째 FND만 켜기 (0xFF00)
    printf("테스트 1: 첫 번째 FND 모든 세그먼트 켜기\n");
    for (int i = 0; i < 20; ++i)
    {
        shiftOut16(fndPatterns[i % 10], fndPatterns[i % 10 + 1]);
        delay(100);
    }

    // FND 끄기
    printf("FND 끄기\n");
    shiftOut16(0x00, 0x00);
    delay(2000);

    printf("테스트 완료\n");
}

void testGyro(int gyro_fd)
{
    printf("Gyro 테스트: 가속도 X축 값 읽기\n");

    // MPU-6050 초기화
    wiringPiI2CWriteReg8(gyro_fd, PWR_MGMT_1, 0x00);   // 슬립 모드 해제
    wiringPiI2CWriteReg8(gyro_fd, ACCEL_CONFIG, 0x00); // 가속도 범위 ±2g
    wiringPiI2CWriteReg8(gyro_fd, GYRO_CONFIG, 0x00);  // 자이로 범위 ±250°/s

    // 캘리브레이션용 오프셋 변수
    int16_t accel_x_offset = 0, accel_y_offset = 0, accel_z_offset = 0;
    int16_t gyro_x_offset = 0, gyro_y_offset = 0, gyro_z_offset = 0;

    const int samples = 100;

    // 캘리브레이션 (정지 상태에서 평균값 계산)
    printf("캘리브레이션 중...\n");
    for (int i = 0; i < samples; i++)
    {
        int16_t ax = wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H) << 8 | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 1);
        int16_t ay = wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 2) << 8 | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 3);
        int16_t az = wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 4) << 8 | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 5);
        int16_t gx = wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H) << 8 | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 1);
        int16_t gy = wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 2) << 8 | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 3);
        int16_t gz = wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 4) << 8 | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 5);

        accel_x_offset += ax;
        accel_y_offset += ay;
        accel_z_offset += az;
        gyro_x_offset += gx;
        gyro_y_offset += gy;
        gyro_z_offset += gz;
        delay(10);
    }
    accel_x_offset /= samples;
    accel_y_offset /= samples;
    accel_z_offset /= samples - 16384; // Z축은 중력(1g = 16384) 보정
    gyro_x_offset /= samples;
    gyro_y_offset /= samples;
    gyro_z_offset /= samples;

    printf("캘리브레이션 완료: ax=%d, ay=%d, az=%d, gx=%d, gy=%d, gz=%d\n",
           accel_x_offset, accel_y_offset, accel_z_offset, gyro_x_offset, gyro_y_offset, gyro_z_offset);

    // 데이터 읽기 루프
    int i = 0;
    while (i < 100)
    {
        // 가속도 데이터 읽기
        int16_t accel_x = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 1);
        int16_t accel_y = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 3);
        int16_t accel_z = (wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, ACCEL_XOUT_H + 5);

        // 자이로 데이터 읽기
        int16_t gyro_x = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 1);
        int16_t gyro_y = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 2) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 3);
        int16_t gyro_z = (wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 4) << 8) | wiringPiI2CReadReg8(gyro_fd, GYRO_XOUT_H + 5);

        // 오프셋 보정
        accel_x -= accel_x_offset;
        accel_y -= accel_y_offset;
        accel_z -= accel_z_offset;
        gyro_x -= gyro_x_offset;
        gyro_y -= gyro_y_offset;
        gyro_z -= gyro_z_offset;

        // 물리 단위로 변환 (선택적)
        float accel_x_g = accel_x / 16384.0; // ±2g 범위
        float accel_y_g = accel_y / 16384.0;
        float accel_z_g = accel_z / 16384.0;
        float gyro_x_dps = gyro_x / 131.0; // ±250°/s 범위
        float gyro_y_dps = gyro_y / 131.0;
        float gyro_z_dps = gyro_z / 131.0;

        // 출력
        printf("Accel (g): X=%.2f, Y=%.2f, Z=%.2f | Gyro (°/s): X=%.2f, Y=%.2f, Z=%.2f\n",
               accel_x_g, accel_y_g, accel_z_g, gyro_x_dps, gyro_y_dps, gyro_z_dps);

        delay(50);
        ++i;
    }
}

void testRGB(int rgb_servo_fd)
{
    printf("RGB 테스트: 빨간색, 녹색, 파란색 순차 점등 (각 1초)\n");

    // PCA9685 초기화
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_MODE1, 0x80);    // 리셋
    delay(10);                                                  // 리셋 후 대기
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_PRESCALE, 0x79); // 주파수 60Hz 설정
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_MODE1, 0x20);    // 활성화 + Auto Increment

    // 빨간색 (CH0)
    printf("빨간색 켜는 중...\n");
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L, 0);        // ON 시간
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 2, 4095); // OFF 시간 (최대 밝기)
    delay(1000);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 2, 0); // 끄기

    // 녹색 (CH1)
    printf("녹색 켜는 중...\n");
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 4, 0);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 6, 4095);
    delay(1000);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 6, 0); // 끄기

    // 파란색 (CH2)
    printf("파란색 켜는 중...\n");
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 8, 0);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 10, 4095);
    delay(1000);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 10, 0); // 끄기

    printf("RGB LED 테스트 완료\n");
}

void testServo(int rgb_servo_fd)
{
    printf("Servo 테스트: Servo1, Servo2 180도에서 0도까지 천천히 회전\n");

    // PCA9685 초기화
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_MODE1, 0x80); // 리셋
    delay(10);
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_PRESCALE, 0x7A); // 50Hz 설정 (정확히)
    wiringPiI2CWriteReg8(rgb_servo_fd, PCA9685_MODE1, 0x20);    // 활성화 + Auto Increment
    delay(10);

    // 서보 펄스 값 계산 (50Hz 기준, 20ms 주기)
    int servo_180 = (int)(4096 * (2.0 / 20.0)); // 약 409 (180도)
    int servo_0 = (int)(4096 * (1.0 / 20.0));   // 약 205 (0도)

    // 초기 위치: 180도
    printf("180도에서 시작...\n");
    // Servo1 (CH4)
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 16, 0);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 18, servo_180);
    // Servo2 (CH5)
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 20, 0);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 22, servo_180);
    delay(1000); // 초기 위치 유지

    // 180도에서 0도까지 천천히 이동
    printf("180도에서 0도까지 천천히 이동 중...\n");
    for (int pulse = 200; pulse >= 0; pulse -= 1)
    {
        // Servo1 (CH4)
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 16, 0);
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 18, pulse);
        // Servo2 (CH5)
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 20, 0);
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 22, pulse);
        delay(100); // 부드러운 이동을 위한 지연
    }

    // 0도에 도달 후 토크 해제
    printf("0도에 도달, 토크 해제 중...\n");
    // Servo1 (CH4) 토크 해제: PWM 신호 끄기
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 16, 0);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 18, 0); // OFF = 0
    // Servo2 (CH5) 토크 해제: PWM 신호 끄기
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 20, 0);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED0_ON_L + 22, 0); // OFF = 0
    delay(500);                                                     // 해제 후 대기

    printf("서보 테스트 완료, 토크 해제됨\n");
}
// OLED 초기화 함수

void testOLED(int oled_fd)
{
    ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

    ssd1306_display(); // Adafruit logo is visible
    ssd1306_clearDisplay();
    delay(5000);
    char *text = "This is demo for SSD1306 i2c driver for Raspberry Pi";
    ssd1306_drawString(text);
    ssd1306_display();
    delay(5000);

    ssd1306_dim(1);
    ssd1306_startscrollright(00, 0xFF);
    delay(5000);

    ssd1306_clearDisplay();
    ssd1306_fillRect(10, 10, 50, 20, WHITE);
    ssd1306_fillRect(80, 10, 130, 50, WHITE);
    ssd1306_display();
}

// void testAll(int touch_fd, int temp_humid_fd, int gyro_fd, int fnd_fd, int rgb_servo_fd, int oled_fd)
// {
//     printf("모든 장치 테스트를 순차적으로 실행합니다...\n\n");

//     testLED();
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testSwitch();
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testPIR();
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testBuzzer();
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testTouchSensor(touch_fd);
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testTempHumid(temp_humid_fd);
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testFND(fnd_fd);
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testGyro(gyro_fd);
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testRGB(rgb_servo_fd);
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testServo(rgb_servo_fd);
//     printf("\n계속하려면 아무 키나 누르세요...\n");
//     getchar();

//     testOLED(oled_fd);

//     printf("\n모든 장치 테스트가 완료되었습니다.\n");
// }