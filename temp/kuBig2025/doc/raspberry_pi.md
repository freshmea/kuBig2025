# 라즈베리파이

---

## 2025-04-01

---

- 1교시
  - 라즈베리파이 OS 이미지 굽기
- 2교시
  - 운영체제론 설명
  - 리눅스 설명 - 오픈 소스, 버전
- 3교시
  - VsCode ssh remote 설정
- 4교시
  - wiringPi 설치
  - GPIO 핀 설정 및 초기화 - add group, set mode 설명(이미 되어 있음)
  - helloRaspberry.c 코드 작성 - 간단한 gpio LED 제어
- 5교시
  - switch_led.c 코드 작성 - 스위치와 LED 제어
  - open 과 write close 로 gpio 제어 -> 작동 안함
- 6교시
  - 커널 설명 - 커널 모드, 사용자 모드, 커널 영역, 사용자 영역
  - system call 설명 - strace 명령어 실습
  - 실습 장비 설명 ES-101(하드웨어 및 핀맵)
- 7교시
  - module_exam.c , Makefile 작성
- 8교시
  - insmod, rmmod 로 커널 모듈 로드 및 언로드
  - 커널 모드와 사용자 모드의 차이점 설명
  - 정리

---

## 2025-04-02

---

- 1교시
  - 복습
  - 여러 프로세스 다루기 ( &, nohup, bg, fg, jobs, ps, kill, top, htop)
- 2교시
  - 데몬으로 프로세스 작동 시키기
- 3교시
  - mydaemon.service 파일, mydaemon.sh 파일 작성
  - systemctl 명령어 설명
- 4교시
  - wiringPi 로 pwm 제어하기, 버저 설정
  - software pwm 제어하기, hardware pwm 제어하기, buzzer 제어하기
- 5교시
  - PCA9685 설명
  - PCA9685 제어하기
- 6교시
  - 커널 모듈 설명
- 7교시
  - RGB LED 제어하기
  - RGB LED 제어하기 - PWM
- 8교시
  - servo 제어하기 - PWM
  - 정리

---

## 2025-04-03

---

- 1교시
  - 복습
  - 커널 모듈 설명
  - led_driver.c 코드 작성
  - Makefile 작성
- 2교시
  - switch_interrupt.c 코드 작성
- 3교시
  - export_symbol 모듈 작성
- 4교시
  - GPL 설명
- 5교시
  - character device driver 설명
  - led_driver.c
- 6교시
  - switch_driver.c 코드 작성
- 7교시
  - led_switch_driver 실습
- 8교시
  - 정리

---

## 2025-04-04

---

[라즈베리파이 하드웨어](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html)
[커널 교재](https://sysprog21.github.io/lkmpg/#sticking-your-head-inside-a-large-carnivore)
[커널 예제 코드](https://github.com/PacktPublishing/Linux-Kernel-Programming)

- 1교시
  - 복습
  - ioremap 설명, 라즈베리파이4B IO register 설명
  - 가상메모리, 물리메모리 설명
  - gpiomem_module.c 코드 작성
- 2교시
  - FND, 74HC595 칩 설명(latch, clock, data)
  - fnd_cnt.c 코드 작성
- 3교시
  - rgb_switch_fnd.c 작성 [실습]
- 4교시
  - PIR 센서 설명 - GPIO 핀 - 인터럽트가 작동 하지 않았음.... 다른 핀과 겹치는듯
  - 터치 센서 값 읽기 - I2C touch_ATQT1070 IC 칩 데이터 시트
- 5교시
  - 온습도 센서 값 읽기 - I2C SHT20 IC 칩 데이터 시트
  - 자이로 센서 값 읽기 - I2C MPU6050 IC 칩 데이터 시트
- 6교시
  - 자이로 센서 활용 실습 - 라즈베리파이4B 실습 상자 움직임 감지 -> 버저, LED 점등
- 7교시
  - 자이로 센서 활용 코드 - gyro_detect.c 작성
  - 오디오 실습 - WM8960 칩 설명
- 8교시
  - dts config.txt 파일 수정, github 커널모듈 설치, aplay -l 확인
  - sound.c 코드 실습 - 스피커 소리 출력 및 마이크 입력 테스트
  - 정리

---

## 2025-04-07

---
[스크립트 코드](https://www.freecodecamp.org/news/bash-scripting-tutorial-linux-shell-script-and-command-line-for-beginners/?utm_source=chatgpt.com)

- 1교시
  - 복습
  - 스크립트 작성법 설명
- 2교시
  - bash 스크립트 작성법 설명
  - hello.sh 코드 작성 - 변수, echo, read, export, 환경변수, local
  - if문, for문, while문, until문 연산자, 논리 연산자, case문
- 3교시
  - 반복문, 함수 설명
  - flow_exec.sh 코드 작성
  - 스크립트 자동화 기법 설명
- 4교시
  - cron 설명, crontab을 사용하여 스크립트 자동 실행하기
  - 스크립트 실행 주기 설정 방법 설명 - crontab -e, crontab -l
  - grep CRON /var/log/syslog
  - 정리
