# ESP32-CAM Python OpenCV Viewer

## 개요

ESP32-CAM의 MJPEG 스트림을 Python OpenCV로 수신하여 실시간으로 화면에 표시하는 프로그램입니다.

## 기능

- ESP32-CAM 실시간 스트리밍 표시
- FPS 계산 및 표시
- 스크린샷 저장 기능
- 스트림 재시작 기능
- 키보드 컨트롤

## 설치

### 자동 설치

```bash
chmod +x install_opencv.sh
./install_opencv.sh
```

### 수동 설치

```bash
pip3 install opencv-python numpy
```

## 사용법

### 기본 실행

```bash
python3 esp32cam_viewer.py
```

### IP 주소 변경

코드에서 다음 부분을 수정:

```python
ESP32_CAM_IP = "192.168.0.103"  # 실제 ESP32-CAM IP로 변경
```

## 키보드 컨트롤

- **q**: 프로그램 종료
- **s**: 스크린샷 저장
- **r**: 스트림 재시작

## 스크린샷

스크린샷은 다음 위치에 저장됩니다:

```
/home/aa/kuBig2025/platformio/screenshots/esp32cam_YYYYMMDD_HHMMSS.jpg
```

## 문제 해결

### 연결 실패

1. ESP32-CAM IP 주소 확인
2. 같은 네트워크에 연결되어 있는지 확인
3. 방화벽 설정 확인

### 느린 스트리밍

1. 네트워크 상태 확인
2. ESP32-CAM 전원 공급 확인
3. WiFi 신호 강도 확인

### OpenCV 설치 문제

```bash
# 시스템 패키지 설치 (Ubuntu/Debian)
sudo apt update
sudo apt install python3-opencv

# 또는 pip로 재설치
pip3 uninstall opencv-python
pip3 install opencv-python
```

## 코드 구조

```
Esp32CamViewer 클래스:
├── __init__(): 초기화
├── initializeCamera(): 카메라 연결
├── startViewing(): 메인 뷰잉 루프
├── addInfoToFrame(): 프레임 정보 표시
├── saveScreenshot(): 스크린샷 저장
├── restartStream(): 스트림 재시작
└── cleanup(): 리소스 정리
```

## 확장 기능

### 녹화 기능 추가 예시

```python
# VideoWriter로 녹화
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640, 480))
```

### 이미지 처리 추가 예시

```python
# 그레이스케일 변환
gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

# 엣지 검출
edges = cv2.Canny(gray, 50, 150)
```
