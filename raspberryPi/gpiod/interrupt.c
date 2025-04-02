#include <gpiod.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
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
#define CONSUMER "interrupt_app"

// LED 상태 저장
int led_state[4] = {0, 0, 0, 0};
struct gpiod_line *led_lines[4];

// 스위치 이벤트 콜백 함수
void handle_switch_event(int sw_num);

// 이벤트 모니터링 스레드용 구조체
typedef struct
{
    struct gpiod_line_bulk *bulk;
    int is_running;
    pthread_t thread;
} event_thread_data;

// 이벤트 모니터링 스레드 함수
void *event_monitor_thread(void *arg);

int main(void)
{
    struct gpiod_chip *chip;
    struct gpiod_line *sw_lines[4];
    struct gpiod_line_bulk bulk;
    event_thread_data event_data;

    int led[4] = {LED1, LED2, LED3, LED4};
    int sw[4] = {SW1, SW2, SW3, SW4};

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
    }

    // 스위치 핀 설정 및 이벤트 검출 준비
    gpiod_line_bulk_init(&bulk);

    for (int i = 0; i < 4; ++i)
    {
        sw_lines[i] = gpiod_chip_get_line(chip, sw[i]);
        if (!sw_lines[i])
        {
            perror("gpiod_chip_get_line (switch)");
            gpiod_chip_close(chip);
            return 1;
        }

        gpiod_line_bulk_add(&bulk, sw_lines[i]);
    }

    // 이벤트 검출 모드로 입력 설정 (상승 에지)
    if (gpiod_line_request_bulk_rising_edge_events(&bulk, CONSUMER) < 0)
    {
        perror("gpiod_line_request_bulk_rising_edge_events");
        gpiod_chip_close(chip);
        return 1;
    }

    // 이벤트 모니터링 스레드 시작
    event_data.bulk = &bulk;
    event_data.is_running = 1;

    if (pthread_create(&event_data.thread, NULL, event_monitor_thread, &event_data) != 0)
    {
        perror("pthread_create");
        gpiod_chip_close(chip);
        return 1;
    }

    // 메인 프로그램은 무한 대기
    while (1)
    {
        sleep(1);
    }

    // 자원 해제 (여기까지 도달하지 않지만 완전성을 위해 포함)
    event_data.is_running = 0;
    pthread_join(event_data.thread, NULL);

    for (int i = 0; i < 4; ++i)
    {
        gpiod_line_release(led_lines[i]);
    }
    gpiod_line_release_bulk(&bulk);
    gpiod_chip_close(chip);

    return 0;
}

void *event_monitor_thread(void *arg)
{
    event_thread_data *data = (event_thread_data *)arg;
    struct gpiod_line_event event;
    struct gpiod_line *line;
    int ret, i;
    struct timespec ts = {1, 0}; // 1초 타임아웃

    while (data->is_running)
    {
        ret = gpiod_line_event_wait_bulk(data->bulk, &ts, NULL);
        if (ret < 0)
        {
            perror("gpiod_line_event_wait_bulk");
            break;
        }
        else if (ret == 0)
        {
            // 타임아웃, 다시 대기
            continue;
        }

        // 어떤 라인에서 이벤트가 발생했는지 확인
        for (i = 0; i < gpiod_line_bulk_num_lines(data->bulk); i++)
        {
            line = gpiod_line_bulk_get_line(data->bulk, i);
            if (gpiod_line_event_read(line, &event) == 0)
            {
                // 스위치 번호 확인
                if (gpiod_line_offset(line) == SW1)
                    handle_switch_event(0);
                else if (gpiod_line_offset(line) == SW2)
                    handle_switch_event(1);
                else if (gpiod_line_offset(line) == SW3)
                    handle_switch_event(2);
                else if (gpiod_line_offset(line) == SW4)
                    handle_switch_event(3);
            }
        }
    }

    return NULL;
}

void handle_switch_event(int sw_num)
{
    // LED 상태 토글
    led_state[sw_num] = !led_state[sw_num];

    // LED 값 설정
    gpiod_line_set_value(led_lines[sw_num], led_state[sw_num]);

    // 상태 출력
    const char *msg[4] = {"SWITCH1", "SWITCH2", "SWITCH3", "SWITCH4"};
    printf("%s %s\n", msg[sw_num], led_state[sw_num] ? "ON" : "OFF");
}