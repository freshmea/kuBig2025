# Changelog

## [Unreleased] - 2024-01-XX

### Added

- ESP32-CAM 보드 설정 추가
- 카메라 관련 라이브러리 의존성 추가
- ESP32-CAM 기본 카메라 코드 템플릿 추가
- Arduino IDE 확장용 ESP32-CAM 프로젝트 추가
- 웹 기반 카메라 스트리밍 기능
- 사진 캡처 및 실시간 스트리밍 엔드포인트
- ESP32 패키지 자동 설치 스크립트 추가
- Arduino CLI 사용 가이드 추가
- PlatformIO ESP32 플랫폼 문제 해결 스크립트 추가
- 수동 문제 해결 명령어 가이드 추가
- PlatformIO 명령어 별칭 설정 스크립트 추가
- PlatformIO 사용법 가이드 추가
- Python OpenCV ESP32-CAM 뷰어 추가
- 실시간 FPS 계산 및 표시 기능
- 스크린샷 저장 기능
- 스트림 재시작 기능
- OpenCV 자동 설치 스크립트
- 멀티스레딩 기반 스트림 처리
- MJPEG 스트림 파싱 로직 개선
- 전체화면 모드 지원
- 연결 상태 확인 기능

### Changed

- platformio.ini를 ESP32-CAM 보드로 수정
- 업로드 속도 및 모니터 속도 최적화
- 파티션 설정을 huge_app.csv로 변경 (메모리 최적화)
- c_cpp_properties.json에 ESP32 관련 include 경로 및 정의 추가
- 컴파일러 표준을 C99/C++17로 설정
- ESP32 플랫폼을 안정적인 6.8.1 버전으로 고정
- 내장 라이브러리(WiFi, WebServer, esp32-camera) 제거
- 빌드 플래그 및 보드 설정 최적화
- fix_platformio.sh에서 VSCode PlatformIO 확장의 pio 명령어 사용
- 시스템 pio 명령어 충돌 문제 해결
- ESP32-CAM 뷰어를 작동하는 main.cpp 코드 기반으로 재작성
- requests 라이브러리 사용으로 스트림 처리 안정성 향상
- 멀티스레딩으로 UI 응답성 개선

### Fixed

- ESP32 패키지 누락 문제 해결
- IntelliSense 경로 설정 개선
- PlatformIO 매니페스트 파일 오류 문제 해결
- 플랫폼 캐시 관련 문제 해결 방법 추가
- 시스템 pio와 VSCode PlatformIO 확장 충돌 문제 해결
- PlatformIO 명령어 경로 자동 탐지 기능 추가
- ESP32-CAM 스트림 연결 안정성 문제 해결
- MJPEG 스트림 파싱 오류 수정
- 프레임 드롭 문제 해결

### Note

- 기존 코드는 main.cpp에서 주석 처리하여 백업 보관
- WiFi SSID와 비밀번호는 실제 값으로 수정 필요
- Arduino IDE 확장에서 직접 ESP32-CAM 코드 업로드 가능
- ESP32 패키지 설치 후 VSCode 재시작 필요
- 플랫폼 문제 발생 시 fix_platformio.sh 스크립트 실행 권장
- 시스템 /usr/bin/pio 제거 후 별칭 설정 권장
- VSCode PlatformIO 확장 사용 시 python3 -m platformio 권장
- ESP32-CAM IP 주소 192.168.0.103으로 정상 스트리밍 확인
- 작동하는 main.cpp 코드 기반으로 Python 뷰어 재작성 완료
- requests 라이브러리 추가 필요 (pip install requests)
