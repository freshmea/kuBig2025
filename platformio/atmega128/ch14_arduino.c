#include <Arduino.h>

void setup()
{
    Serial.begin(9600); // 시리얼 통신 시작
    pinMode(16, OUTPUT);
    // DDRC = 0x0F;
}

void loop()
{
    // PORTC = 0x0F;
    digitalWrite(16, HIGH);
    Serial.println("LED ON");
    delay(1000);
    // PORTC = 0x00;
    digitalWrite(16, LOW);
    Serial.println("LED OFF");
    delay(1000);
}