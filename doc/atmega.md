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
- 7교시
- 8교시

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
- 5교시
- 6교시
- 7교시
- 8교시

---

## 2025-03-21

---

- 1교시
- 2교시
- 3교시
- 4교시
- 5교시
- 6교시
- 7교시
- 8교시
