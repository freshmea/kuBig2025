#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint8_t ledData = 0x00;
volatile uint8_t timer1Cnt = 0;

int main()
{
    DDRC = 0x0F; // 1, 2, 3, 4 출력 설정

    TCCR1A = 0x00;
    TCCR1B = 0x01; // 분주비 1 16Mhz 16000000/65535 =

    TIMSK = 0x04;

    sei(); // 전역 인터럽트 허용

    while (1)
    {
        if (timer1Cnt == 255)
        {
            ledData++;
            if (ledData > 0x0F)
                ledData = 0;
            timer1Cnt = 0;
        }
        PORTC = ledData;
    }
    return 0;
}

ISR(TIMER1_OVF_vect)
{
    cli();
    timer1Cnt++;
}