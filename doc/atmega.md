# Atmega128

---

## 2025-03-17

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
