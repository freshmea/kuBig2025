#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>

#define DATA_PIN 0
#define LATCH_PIN 5
#define CLOCK_PIN 6

uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};

void bit_74HC595_shift16(uint8_t digit1, uint8_t digit2);

int main(void)
{
}

void bit_74HC595_shift16(uint8_t digit1, uint8_t digit2)
{
    uint16_t data = (digit1 << 9) | (digit2 << 1);

    for (int i = 15; i >= 0; i--)
    {
        digitalWrite(LATCH_PIN, LOW);
        digitalWrite(CLOCK_PIN, LOW);
        digitalWrite(DATA_PIN, (data >> i) & 1);
        // xxxxxxxx0 or xxxxxxxx1 & 0000000001
        digitalWrite(LATCH_PIN, HIGH);
        digitalWrite(CLOCK_PIN, HIGH);
        delayMicroseconds(10);
    }
    digitalWrite(LATCH_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(LATCH_PIN, HIGH);
}