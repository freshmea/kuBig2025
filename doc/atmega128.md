# Atmega128

---

## 2025-03-18

---

- 1교시
  - 사업 안내 - 국민취업지원 제도안내
- 2교시
  - 복습
  - MCU 에 대한 설명
- 3교시
  - Atmega128 소개
- 4교시
  - platformio 설치
  - 간단한 프로그램 작성 - PORTC 레지스트 변경 및 딜레이
- 5교시
  - permission 문제 해결
    - lsusb -> usb 장치 확인
    - ls -l /dev/bus/usb/001/009 -> 장치 접근 권한 확인
    - sudo chmod 666 /dev/bus/usb/001/009 -> 장치 접근 권한 변경
    - SUBSYSTEM=="usb", ATTR{idVendor}=="03eb", ATTR{idProduct}=="2104", MODE="0666"
- 6교시
  - 간단한 프로그램 작성 - PORTC 레지스트 변경 및 딜레이
  - 좌우로 반복하는 LED 코드 완성
- 7교시
  - 입력 프로그램 작성 스위치
  - PINE 레지스터
  - PINE 레지스터를 사용하여 스위치 입력
- 8교시
  - 정리

---

## 2025-03-19

---

- 1교시
  - 복습
  - switch 예제
- 2교시
  - chattering  문제
  - 디바운싱 해결
- 3교시
  - _delay_ms() 없이 디바운싱 문제 해결
- 4교시
  - FND 실습 - 7세그먼트, no _delay code
  - FND 실습 - 버튼과 연결해서 숫자를 바꾸는 코드
- 5교시
  - 인터럽트 - 타이머 인터럽트, 외부 인터럽트 , 인터럽트 벡터 테이블
- 6교시
  - 외부 인터럽트 활용 프로그램 - FND 과제
  - uart 설명
- 7교시
  - uart 를 이용한 FND 숫자 출력 - PC -> Atmega128
  - uart0 라이브러리 작성 및 적용
- 8교시
  - 정리

---

## 2025-03-20

---

- 1교시
  - 복습
  - uart0.h uart1.c 라이브러리 작성
- 2교시
  - udev 세팅
    - sudo nano /etc/udev/rules.d/99-avrisp.rules
    - sudo udevadm control --reload
    - sudo udevadm trigger
  - stream 설정
    - stdout, stdin -> FDEV_SETUP_STREAM
- 3교시
- 4교시
  - uart3 실습 파일 스위치 정보 PC 로 전송
  - uart3 실습 파일 PC 에서 스트링 정보 Atmega128 로 전송
- 5교시
  - ADC 실습 - 조도 센서 프린트
  - timer0 실습 - LED 제거 1초 세팅
- 6교시
  - timer2 실습 - TCCR2 설정시 주의  TCCR0 와 다름
- 7교시
  - pwm 구현 timer0 비교기 compare output mode 설정
- 8교시
  - 정리

---

## 2025-03-21

---

- 1교시
  - 복습
  - 16비트 타이머timer1 오버플로우 벡터로 LED 점멸
- 2교시
  - 16비트 타이머timer3 오버플로우 벡터로 LED 좌우 이동
- 3교시
  - 16비트 타이머3 캡쳐 인터럽트  - 외부 인터럽트
- 4교시
  - 16비트 타이머1 compare 인터럽트 - 버튼 누른 시간 출력 FND
  - 16비트 타이머1 FND 숫자 증가 및 감소 compare 및 overflow 인터럽트 동시 사용
- 5교시
  - PWM buzzer - 도레미 출력 OC 핀 설정
- 6교시
  - buzzer, 버튼, FND 통합 예제 [실습] - ch7_3_buzzerapp
- 7교시
  - servopwm 제어
- 8교시
  - 정리

---

## 2025-03-24

---

- 1교시
  - 복습
  - DC 모터 제어
- 2교시
  - DC 모터 PWM 제어
- 3교시
  - 동기 방식, 비동기 방식, 전이중 방식, 반이중 방식 에 의한 분류(SPI, I2C, UART, one-wire)
  - SPI 설명 및 실습 - 외부 eeprom 예제
- 4교시
  - 메모리 종류(flash, sram, eeprom)와 내부 eeprom
  - ic2 통신 설명
- 5교시
- 6교시
- 7교시
- 8교시
