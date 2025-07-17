void setup()
{
    // 시리얼 통신 초기화 (9600 baud rate)
    Serial.begin(9600);

    // 연결 대기
    while (!Serial)
    {
        ; // 시리얼 포트가 연결될 때까지 대기
    }

    // 시작 메시지 출력
    Serial.println("Arduino Echo Server Started!");
    Serial.println("Type something and press Enter...");
}

void loop()
{
    // 시리얼 포트에 데이터가 있는지 확인
    if (Serial.available() > 0)
    {
        // 문자열을 읽어오기
        String inputString = Serial.readString();

        // 앞뒤 공백 제거
        inputString.trim();

        // 에코 - 받은 내용을 다시 전송
        Serial.print("Echo: ");
        Serial.println(inputString);
    }
}