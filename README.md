# kuBig2025

이 저장소는 고려대 세종캠퍼스에서 C 수업을 할때 쓰는 저장소입니다.

- 공유 슬라이드 :
  - [링크](https://docs.google.com/presentation/d/1hUhaFz0kHQDm4hWiixyNaFHurTdKVZKouBQJ8HChjd0/edit#slide=id.p)

---

## C 언어

---

- 수업 목표
  - C언어를 배워 프로그래밍 능력을 향상 시키며 TCP/IP 소켓프로그래밍 학습을 통해 프로그램 능력을 향상 시킬 수 있다.
  - 기본적인 프로젝트 관리와 CMake를 이용한 빌드 방법을 익힌다.
  - VsCode 를 활용하는 기술을 익히고 디버깅 방법을 익힌다.
  - 최종 프로젝트 - 볼링 게임(MySql 연동)
- [과정 진행 사항](doc/c_programming.md)
- 시험 링크 : [구글 설문지](https://forms.gle/xcMTavAxecmgJHL98)

---

## Atmega128 - embedded programming

---

- 수업 목표
  - Atmega128을 이용한 임베디드 프로그래밍을 통해 하드웨어와 소프트웨어를 연결하는 방법을 익힌다.
  - Atmega128의 기본적인 사용법을 익히고 이를 이용한 프로젝트를 수행한다.
  - Atmega128의 입출력을 이용한 프로젝트를 수행한다.
- [과정 진행 사항](doc/atmega128.md)
- 시험 링크 : [구글 설문지]()

---

## Project 1 - C Programming, Mysql, Atmega128

---

- 프로젝트 목표
  - C언어를 이용한 프로그램을 작성하고 Mysql과 연동하여 데이터를 저장하고 읽는 방법을 익힌다.
  - Atmega128을 이용한 프로젝트를 수행하고 이를 Mysql과 연동하여 데이터를 저장하고 읽는 방법을 익힌다.
- 프로젝트 깃링크
  - [1조](https://github.com/example/group1)
  - [2조](https://github.com/example/group2)
  - [3조](https://github.com/example/group3)

---

### ES-101 테스트

- wifi-접속
- 비번 변경 - sudo passwd [사용자이름]
- 파일 복사 - scp [파일이름] [사용자이름]@[ip주소]:[경로]
  - `scp -r es101_test/ hotari@192.168.0.43:~/`
- I2S 장치 설정
  - sudo nano /boot/config.txt ->
    - dtparam=audio=off
    - dtoverlay=i2s-mmap
    - dtoverlay=wm9860-soundcard
  - git clone https://github.com/waveshare/WM8960-Audio-HAT
  - cd WM8960-Audio-HAT/
  - sudo ./install.sh
- sudo apt-get install libasound2-dev
- aplay -l 에서 확인된 채널과 디바이스 번호로 코드를 수정한다. 324번 라인

- SD 카드 포맷 순서
  - imager 다운로드
  - raspberry pi 4B 선택-> image 만들기
  - 라즈베리파이4에 꽂아서 실행
    - 언어설정
    - wifi 설정
    - 사용자 아이디/비밀번호 설정
    - 호스트 명 변경
    - sudo raspi-config -> vnc 설정, ssh 설정, spi 설정, i2c 설정 ...

- SD 카드 포맷 (ubuntu)
  - ssh 설치
    - 패키지 업데이트: sudo apt-get update
    - ssh 설치: sudo apt-get install openssh-server
    - vnc 설정: sudo apt install tigervnc-standalone-server tigervnc-common -y -- 포기
    - 빌드 설치: sudo apt-get install build-essential make git
    - 사용자 권한 설정: sudo usermod -aG dialout $USER
    - 비디오 권한 설정: sudo usermod -aG video $USER
    - 비디오 드라이버: sudo apt install libraspberrypi-bin v4l-utils sudo apt install libcamera-tools
    - 비디오 체크: v4l2-ctl --list-devices
    - wm8960 설정은 라즈비안 에서는 되지만 ubuntu에서는 안됨 -> sound card 설정이 안됨 해결방법이 아직 없음.

---

## 라즈베리파이4 B

---

- 수업 목표
  - 라즈베리파이 OS 를 이해 한다.
- [과정 진행 사항](doc/raspberry_pi.md)
- 시험 링크 : [구글 설문지]()