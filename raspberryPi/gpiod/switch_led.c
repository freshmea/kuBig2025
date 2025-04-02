#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

// gpio pin
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1
#define SW1 4
#define SW2 17
#define SW3 27
#define SW4 22

#define CHIP_NAME "gpiochip0"
#define CONSUMER "switch_led_app"

int main(void)
{
    struct gpiod_chip *chip;
    struct gpiod_line *led_lines[4];
    struct gpiod_line *sw_lines[4];

    int led[4] = {LED1, LED2, LED3, LED4};
    int sw[4] = {SW1, SW2, SW3, SW4};

    // gpiod 칩 열기
    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip)
    {
        perror("gpiod_chip_open_by_name");
        return 1;
    }

    // LED 및 스위치 핀 설정
    for (int i = 0; i < 4; ++i)
    {
        // LED 설정
        led_lines[i] = gpiod_chip_get_line(chip, led[i]);
        if (!led_lines[i])
        {
            perror("gpiod_chip_get_line (led)");
            gpiod_chip_close(chip);
            return 1;
        }

        if (gpiod_line_request_output(led_lines[i], CONSUMER, 0) < 0)
        {
            perror("gpiod_line_request_output");
            gpiod_chip_close(chip);
            return 1;
        }

        // 스위치 설정
        sw_lines[i] = gpiod_chip_get_line(chip, sw[i]);
        if (!sw_lines[i])
        {
            perror("gpiod_chip_get_line (switch)");
            gpiod_chip_close(chip);
            return 1;
        }

        if (gpiod_line_request_input(sw_lines[i], CONSUMER) < 0)
        {
            perror("gpiod_line_request_input");
            gpiod_chip_close(chip);
            return 1;
        }
    }

    // 메인 루프
    while (1)
    {
        for (int i = 0; i < 4; ++i)
        {
            int sw_value = gpiod_line_get_value(sw_lines[i]);
            gpiod_line_set_value(led_lines[i], sw_value);
        }
        usleep(10000); // 10ms 대기
    }

    // 자원 해제 (여기까지 도달하지 않지만 완전성을 위해 포함)
    for (int i = 0; i < 4; ++i)
    {
        gpiod_line_release(led_lines[i]);
        gpiod_line_release(sw_lines[i]);
    }
    gpiod_chip_close(chip);

    return 0;
}