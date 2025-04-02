#include <gpiod.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define BUZZER_PIN 12
#define CHIP_NAME "gpiochip0"
#define CONSUMER "buzzer_app"

int doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

void softwareTone(struct gpiod_line *line, int freq, int duration_ms);

int main(void)
{
    struct gpiod_chip *chip;
    struct gpiod_line *buzzer_line;

    // gpiod 칩 열기
    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip)
    {
        perror("gpiod_chip_open_by_name");
        return 1;
    }

    // 부저 핀 가져오기
    buzzer_line = gpiod_chip_get_line(chip, BUZZER_PIN);
    if (!buzzer_line)
    {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
        return 1;
    }

    // 출력 모드로 설정
    if (gpiod_line_request_output(buzzer_line, CONSUMER, 0) < 0)
    {
        perror("gpiod_line_request_output");
        gpiod_line_release(buzzer_line);
        gpiod_chip_close(chip);
        return 1;
    }

    // 도레미파솔라시도 순으로 소리 출력
    while (1)
    {
        for (int i = 0; i < 8; ++i)
        {
            softwareTone(buzzer_line, doReMi[i], 1000);
        }
    }

    // 자원 해제
    gpiod_line_release(buzzer_line);
    gpiod_chip_close(chip);

    return 0;
}

void softwareTone(struct gpiod_line *line, int freq, int duration_ms)
{
    // 주파수에 따른 주기 계산 (마이크로초 단위)
    int period_us = 1000000 / freq;
    int high_us = period_us / 2; // 50% 듀티 사이클

    // 지정된 시간 동안 톤 생성
    struct timespec start_time, current_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    long elapsed_ms = 0;
    while (elapsed_ms < duration_ms)
    {
        // HIGH 상태
        gpiod_line_set_value(line, 1);
        usleep(high_us);

        // LOW 상태
        gpiod_line_set_value(line, 0);
        usleep(period_us - high_us);

        // 경과 시간 계산
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        elapsed_ms = (current_time.tv_sec - start_time.tv_sec) * 1000 +
                     (current_time.tv_nsec - start_time.tv_nsec) / 1000000;
    }
}