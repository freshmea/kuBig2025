// cc helloRaspberry.c -lgpiod

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

// 라즈베리파이의 GPIO 칩 이름 (보통 "gpiochip0")
#define CHIP_NAME "gpiochip0"
// gpio pin
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

int main(void)
{
    struct gpiod_chip *chip;
    struct gpiod_line *led1;
    int ret;

    // GPIO 칩 열기
    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip)
    {
        perror("gpiod_chip_open_by_name");
        return 1;
    }

    // LED1 핀에 해당하는 라인 가져오기
    led1 = gpiod_chip_get_line(chip, LED1);
    if (!led1)
    {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
        return 1;
    }

    // LED1을 출력 모드로 설정
    ret = gpiod_line_request_output(led1, "helloRaspberry", 0);
    if (ret < 0)
    {
        perror("gpiod_line_request_output");
        gpiod_chip_close(chip);
        return 1;
    }

    // LED1 켜기
    gpiod_line_set_value(led1, 1);

    printf("안녕하세요!\n");

    // 무한 반복 (LED 켜진 상태 유지)

    sleep(3);
    // LED1 끄기
    gpiod_line_set_value(led1, 0);

    // 자원 해제 (실제로는 무한 루프 때문에 실행되지 않음)
    gpiod_line_release(led1);
    gpiod_chip_close(chip);

    return 0;
}