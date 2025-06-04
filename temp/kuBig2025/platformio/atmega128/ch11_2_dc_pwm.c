#include <avr/delay.h>
#include <avr/io.h>

int main(void)
{
    DDRD = _BV(PD4) | _BV(PD5); // 출력 설정
    DDRB = _BV(PB5);

    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(CS11) | _BV(WGM12) | _BV(WGM13);
    // fast pwm 분주비 8 -> 16MHz/8 = 2MHz
    ICR1 = 800;  // 2MHz : 1 초 == 800 Hz : x 초 ... 2500 Hz
    OCR1A = 560; // 800 카운트 하는데 560 번까지 -> 5V 70 %

    while (1)
    {
        PORTD |= _BV(PD4); // M1 정회전
        PORTB |= _BV(PB5); // M1 회전 enable
        _delay_ms(500);
        PORTD &= ~_BV(PD4); // 0bXXX1XXXX -> & (0b 11101111 )
        PORTD |= _BV(PD5);  // M1 역회전 - 속도 영향 ? --
        PORTB |= _BV(PB5);  // M1 회전 enable
        _delay_ms(500);
    }

    return 0;
}