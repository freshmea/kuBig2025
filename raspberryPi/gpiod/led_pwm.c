#include <gpiod.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// gpio pin
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

#define CHIP_NAME "gpiochip0"
#define CONSUMER "led_pwm_app"

// PWM 스레드용 구조체
typedef struct
{
    struct gpiod_line *line;
    int duty;         // 0-255
    int max_duty;     // 255
    int is_running;   // 스레드 실행 여부
    pthread_t thread; // 스레드 ID
} pwm_thread_data;

// PWM 스레드 함수
void *pwm_thread(void *arg);

int main(void)
{
    struct gpiod_chip *chip;
    struct gpiod_line *led_lines[4];
    pwm_thread_data pwm_data[4];

    int led[4] = {LED1, LED2, LED3, LED4};

    // gpiod 칩 열기
    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip)
    {
        perror("gpiod_chip_open_by_name");
        return 1;
    }

    // LED 핀 설정
    for (int i = 0; i < 4; ++i)
    {
        led_lines[i] = gpiod_chip_get_line(chip, led[i]);
        if (!led_lines[i])
        {
            perror("gpiod_chip_get_line");
            gpiod_chip_close(chip);
            return 1;
        }

        if (gpiod_line_request_output(led_lines[i], CONSUMER, 0) < 0)
        {
            perror("gpiod_line_request_output");
            gpiod_chip_close(chip);
            return 1;
        }

        // PWM 데이터 초기화
        pwm_data[i].line = led_lines[i];
        pwm_data[i].max_duty = 255;
        pwm_data[i].is_running = 1;

        // PWM 초기값 설정
        if (i == 0)
            pwm_data[i].duty = 255; // LED1
        else if (i == 1)
            pwm_data[i].duty = 120; // LED2
        else
            pwm_data[i].duty = 0; // LED3, LED4

        // PWM 스레드 시작
        if (pthread_create(&pwm_data[i].thread, NULL, pwm_thread, &pwm_data[i]) != 0)
        {
            perror("pthread_create");
            gpiod_chip_close(chip);
            return 1;
        }
    }

    // LED4 밝기를 점점 증가시키는 메인 루프
    while (1)
    {
        for (int i = 0; i < 255; ++i)
        {
            pwm_data[3].duty = i; // LED4
            usleep(100000);       // 100ms
        }
    }

    // 자원 해제 (여기까지 도달하지 않지만 완전성을 위해 포함)
    for (int i = 0; i < 4; ++i)
    {
        pwm_data[i].is_running = 0;
        pthread_join(pwm_data[i].thread, NULL);
        gpiod_line_release(led_lines[i]);
    }
    gpiod_chip_close(chip);

    return 0;
}

void *pwm_thread(void *arg)
{
    pwm_thread_data *data = (pwm_thread_data *)arg;

    while (data->is_running)
    {
        if (data->duty > 0)
        {
            gpiod_line_set_value(data->line, 1);
            usleep(data->duty * 100); // 최대 25.5ms HIGH
        }

        if (data->duty < data->max_duty)
        {
            gpiod_line_set_value(data->line, 0);
            usleep((data->max_duty - data->duty) * 100); // 나머지 시간 LOW
        }
    }

    return NULL;
}