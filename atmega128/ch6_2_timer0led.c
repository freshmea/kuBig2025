// timer2 번을 써서 LED 좌우로 움직이는 코드 작성. 0.3초마다 움직이기.

#include <avr/interrupt.h>
#include <avr/io.h>

volatile uint8_t ledData = 0x00;
uint8_t timer0Cnt = 0;
ISR(TIMER0_OVF_vect);

int main(void)
{
    DDRC = 0x0F;

    TCCR0 = _BV(CS02) | _BV(CS01) | _BV(CS00); // clock select 1024 prescale
    // TCNT0 = 112;                               // 114 * 1024 prescale Hz 160000/1024*114 --> 10ms
    TIMSK = _BV(TOIE0); // timer interrupt en.
    // TIFR |= _BV(TOV0); 없어도 됨

    sei();
    uint8_t direction = 0;
    while (1)
    {
        if (timer0Cnt == 100)
        {
            if (ledData > 0x04)
                direction = 0;
            if (ledData == 1)
            {
                direction = 1;
                ledData = 1;
            }

            if (direction)
                ledData <<= 1;
            else
                ledData >>= 1;
            timer0Cnt = 0;
        }
        PORTC = ledData;
    }
}

ISR(TIMER0_OVF_vect)
{
    cli();
    TCNT0 = 112; // 113, 114 .... 255 .. 144-> 0.0025 초
    timer0Cnt++;
    sei();
}